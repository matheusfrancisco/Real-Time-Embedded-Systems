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

void read_pipee()
{
  char msg_recebida;

}


void writee_pipe()
{   
  // Configura portas
    /*
  TRISDbits.RD0 = 0;                                                         
  PORTDbits.RD0 = 0;
  TRISDbits.RD1 = 0;                                                         
  PORTDbits.RD1 = 0;
  TRISDbits.RD2 = 0;                                                         
  PORTDbits.RD2 = 0;
 
  char dados[2] = {'R', 'Y'};
  u_int index_send = 0;

    while(1)
    {
    PORTDbits.RD2 = ~LATDbits.LD2;
    pipe_write(&msg, dados[index_send]);
    index_send = (index_send+1) % 2;    
    // Aguarda por 200 ms
    delay(200);
    }*/
}
