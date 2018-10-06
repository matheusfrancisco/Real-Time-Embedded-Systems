/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include "kernel.h"
#include "scheduler.h"

#define QUANTUM 4

u_int quantum = QUANTUM;

tcb_t F_APTOS[MAX_TASKS];
u_int tasks_installed = 0;
u_int task_running = 0;

void create_task(u_int id, u_int prior, f_ptr task_f)
{
  tcb_t task;
  
  task.task_id                = id;
  task.task_prior             = prior;
  task.task_f                 = task_f;  
  task.task_stack.stack_size  = 0;
  task.task_state             = READY;
  
  F_APTOS[tasks_installed]    = task;
  tasks_installed++;
}

void dispatcher(state_t state)
{ 
  di();
  
  // Salva o contexto da tarefa que sairá de execução
  SAVE_CONTEXT(state);
  
  // Escolhe a tarefa que será executada
  task_running = rr_scheduler();
  
  // Restaura o contexto da tarefa que entrará em execução
  RESTORE_CONTEXT();
  
  ei();
}

u_int get_id(u_int task_ptr)
{
  return F_APTOS[task_ptr].task_id;
}

void delay(u_int time_ms)
{
  di();
  
  F_APTOS[task_running].delay_time = time_ms;
  dispatcher(SLEEPING);
  
  ei();
}

void task_idle()
{
  TRISDbits.RD4 = 0;   
  
  while (1) { 
    PORTDbits.RD4 = ~PORTDbits.RD4;
    NOP();
  }
}


void setupOS()
{
  // Timer
  // Configuração para o timer estourar a cada
  // 4 ms
  // Configuração considerando o timer 0 8 bits
  T0CONbits.T0CS      = 0;
  T0CONbits.PSA       = 0;
  T0CONbits.T0PS      = 0b111;
  INTCONbits.PEIE     = 1;
  INTCONbits.TMR0IE   = 1;  
  TMR0L               = 252;
  
  // Instalar a tarefa idle
  create_task(1,5, &task_idle);  
 
  //dispatcher(READY);
  
  ei();
}

void interrupt int_high()
{
  u_int i;
  
  if (INTCONbits.TMR0IF) {
    INTCONbits.TMR0IF = 0;
    TMR0L = 252;
    // Verifica se tem tarefa em modo SLEEPING
    for (i = 1; i < tasks_installed; i++) {
      if (F_APTOS[i].task_state == SLEEPING) {
        F_APTOS[i].delay_time--;
        if (F_APTOS[i].delay_time == 0) {
          F_APTOS[i].task_state = READY;
        }
      }
    }
    // Decrementa o quantum
    quantum--;
    if (quantum == 0) {
      quantum = QUANTUM;
      dispatcher(READY);
    }
  }
}

void start_os()
{
  // Liga o timer
  //asm("PUSH");
  //TOS = F_APTOS[task_running].task_f;
  T0CONbits.TMR0ON    = 1;  
}
