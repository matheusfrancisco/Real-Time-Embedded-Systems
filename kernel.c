/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include "kernel.h"
#include "scheduler.h"
#include "memory.h"
#include "config.h"
#include "lcd.h"


#define QUANTUM 4

u_int quantum = QUANTUM;

tcb_t F_APTOS[MAX_TASKS];
u_int tasks_installed = 0;
u_int task_running = 0;

void create_task(u_int id, u_int prior, f_ptr task_f)
{
  //di();
  tcb_t task;
  
  task.task_id                = id;
  task.task_prior             = prior;
  task.task_f                 = task_f;  
  task.task_stack.stack_size  = 0;
  task.task_state             = READY;
  
  F_APTOS[tasks_installed]    = task;
  tasks_installed++;
 // ei();
}

void dispatcher(state_t state)
{ 
  di();
  
  // Salva o contexto da tarefa que sair� de execu��o
  SAVE_CONTEXT(state);
  
#if RR_SCH
  // Escolhe a tarefa que ser� executada
  task_running = rr_scheduler();
  
#else
   task_running = prior_scheduler();

#endif
  // Restaura o contexto da tarefa que entrar� em execu��o
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
  //TRISBbits.RB6 = 0;
  //PORTDbits.RD4 =0;
 
  
  while (1) { 
     //PORTBbits.RB6 =~LATBbits.LATB6;
   // NOP();
  }
}


void setupOS()
{
  // Timer
  // Configura��o para o timer estourar a cada
  // 4 ms
  // Configura��o considerando o timer 0 8 bits
  //INTCONbits.TMR0IE   = 1;
  //INTCONbits.TMR0IF   = 0;
 // INTCONbits.GIE      = 1;
 // T0CONbits.T0CS      = 0;
 // T0CONbits.PSA       = 0;
 // T0CONbits.T0PS      = 0b111;
  T0CONbits.T0CS      = 0;
  T0CONbits.PSA       = 0;
  T0CONbits.T0PS      = 0b111;
  INTCONbits.PEIE     = 1;
  INTCONbits.TMR0IE   = 1;  
  TMR0L               = 252;
  //1 ms: 256 - (0,001 * 4000000) / (256 (preescaler) * 4 (MCY)) = 252
    T0CONbits.TMR0ON    = ON;
  //start_os();
  //TMR0L               = 252;
  //TMR0                 = 64911;
  // Instalar a tarefa idle
  //create_task(1,5, &task_idle);  
 
  //dispatcher(READY);
  //TRISCbits.RC1 = 0;
  //TRISCbits.RC2 = 0;
  //TRISCbits.RC3 = 0;
  //TRISCbits.RC4 = 0;
  
  //TRISEbits.RE0 = 0;
  //TRISEbits.RE1 = 0;
  
  //Lcd_Init();
    TRISBbits.RB0 = 0;

  SRAMInitHeap();
  
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

  T0CONbits.TMR0ON    = 1;  
}
