/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <pic18f4520.h>
#include "tasks.h"
#include "kernel.h"
#include "semaphore.h"
#include "pipe.h"
sem_t s;

pipe_t pipe;

void task_one()
{
  TRISDbits.RD0 = 0;
  PORTDbits.RD0 = 0;
  
  sem_init(&s, 1);
  
  while (1) {
    sem_wait(&s);
    PORTDbits.RD0 = ~PORTDbits.RD0;
    //sem_post(&s);
    delay(100);    
  }
}

void task_two()
{
  TRISDbits.RD1 = 0;
  PORTDbits.RD1 = 0;

  while (1) {
    //sem_wait(&s);
    PORTDbits.RD1 = ~PORTDbits.RD1;    
    delay(100);
    //sem_post(&s);
  }
}

void task_thre()
{
  TRISDbits.RD3 = 0;
  PORTDbits.RD3 = 0;

  while (1) {
    PORTDbits.RD3 = ~PORTDbits.RD3;
    delay(100);
  }
}


void task_one_pipe()
{
  TRISDbits.RD0 = 0;
  PORTDbits.RD0 = 0;
  
  create_pipe(&pipe);
  
  
  while (1) {
    //sem_wait(&s);
    write_pipe(&pipe, 'a');
    PORTDbits.RD0 = ~PORTDbits.RD0;
    //sem_post(&s);
    delay(100);    
  }
}
void task_one_read()
{
  TRISDbits.RD0 = 0;
  PORTDbits.RD0 = 0;
  byte dado;
  
  
  while (1) {
    //sem_wait(&s);
    dado = read_pipe(&pipe);
    PORTDbits.RD0 = ~PORTDbits.RD0;
    //sem_post(&s);
    delay(100);    
  }
}
