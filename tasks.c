/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <pic18f4520.h>
#include "tasks.h"
#include "kernel.h"
//#include "semaphore.h"
#include "pipe.h"

pipe_t  pipe1 ;
aviao_t aviaozinho1 ;
aviao_t aviaozinho2 ;
pista_t pista ;

aviao_t createAviao(aviao_t *av, u_int tempo_v, u_int tempo_p, u_int numero )
{
 av = (aviao_t*) SRAMalloc(sizeof(aviao_t));

 av->numero =numero;
 av->tempo_p = tempo_p;
 av->tempo_v = tempo_v;
 //return av;
}

void aviao1()
{
    // ideia é criar um aviao
   createAviao(&aviaozinho1,100,100, 1);
  // criar um pipe que seria a comunicacao do aviao
   
  //TRISDbits.RD1 = 0;
  //PORTDbits.RD1 = 0;
 //  pipe1 = (pipe1*) SRAMalloc(sizeof(pipe1));
  create_pipe(&pipe1);
  while (1) {
    //sem_wait(&s);

    //PORTDbits.RD1 = ~PORTDbits.RD1;    
      write_pipe(&pipe1, 'l');
     //delay(100);
    //sem_wait(&s);
  }
}

void aviao2()
{
    // ideia é criar um aviao
    //aviaozinho2 = (aviao_t*) SRAMalloc(sizeof(aviao_t));
   createAviao(&aviaozinho2,1000,200, 1);
  // criar um pipe que seria a comunicacao do aviao
   //pipe_t  pipe2 = (pipe2*) SRAMalloc(sizeof(pipe2));
   
  //TRISDbits.RD1 = 0;
  //PORTDbits.RD1 = 0;
   //pipe1 = (pipe1*) SRAMalloc(sizeof(pipe1));

  create_pipe(&pipe1);
  while (1) {
    //sem_wait(&s);

    //PORTDbits.RD1 = ~PORTDbits.RD1;    
      write_pipe(&pipe1, 'm');
     //delay(100);
    //sem_wait(&s);
  }
}

void ctpista()
{
    //pista = (pista_t*) SRAMalloc(sizeof(pista_t));
    
    while(1)
    {
        byte dado = read_pipe(&pipe1);
        if(dado== 'l')
        {
            
            TRISDbits.RD1 = 0;
            PORTDbits.RD1 = 0;
            u_int n = aviaozinho1.numero;
            u_int tv = aviaozinho1.tempo_v;
            u_int tp = aviaozinho1.tempo_p;
            PORTDbits.RD1 = ~PORTDbits.RD1;
            pista.aviaozinho.numero=n;
            pista.status = 1;
            sem_wait(&pista.s);
            delay(tv+tp);
            sem_post(&pista.s);
            pista.status = 0;
            pista.aviaozinho.numero= 0;
            //SRAMfree(pipe1);
            //delay(tv+tp);
            
            
        }
        if(dado=='m')
        {
            TRISDbits.RD2 = 0;
            PORTDbits.RD2 = 0;
            u_int n = aviaozinho2.numero;
            u_int tv = aviaozinho2.tempo_v;
            u_int tp = aviaozinho2.tempo_p;
            PORTDbits.RD2 = ~PORTDbits.RD2;
            pista.aviaozinho.numero=n;
            pista.status = 1;
            sem_wait(&pista.s);
            delay(tv+tp);
            sem_post(&pista.s);
            pista.status = 0;
            pista.aviaozinho.numero= 0;
            //SRAMfree(pipe1);
        }
    }
}