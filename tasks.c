/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <pic18f4520.h>
#include "tasks.h"
#include "kernel.h"
#include "semaphore.h"
#include "pipe.h"

sem_t *s;
pipe_t pipe;



void aviao2()
{
  byte dado;
  
  TRISDbits.RD1 = 0;
  PORTDbits.RD1 = 0;
  create_pipe(&pipe);
  while (1) {
    //sem_wait(&s);

    //PORTDbits.RD1 = ~PORTDbits.RD1;    
      write_pipe(&pipe, 2);
     //delay(100);
    //sem_wait(&s);
  }
}

void aviao3()
{
  TRISDbits.RD3 = 0;
  PORTDbits.RD3 = 0;

  while (1) {
    //PORTDbits.RD3 = ~PORTDbits.RD3;
      write_pipe(&pipe, 3);
      delay(100);
    //sem_wait(&s);
  }
}

void ctpista()
{
    while(1)
    {
        int dado = read_pipe(&pipe);
        if(dado== 2)
        {
            sem_post(&s);
            PORTDbits.RD3 = ~PORTDbits.RD3;
            delay(1000);
            sem_wait(&s);
            
        }
        if(dado==3)
        {
            sem_post(&s);
            PORTDbits.RD2 = ~PORTDbits.RD2;
            delay(1000);
            sem_wait(&s);
        }
    }
}