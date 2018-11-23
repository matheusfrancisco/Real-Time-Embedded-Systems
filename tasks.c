/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <pic18f4520.h>
#include "tasks.h"
#include "kernel.h"
#include "pipe.h"
#include "lcd.h"
#include "memory.h"



sem_t spista;
u_int cont = 0;

pipe_t pipeluzes;
pipe_t testL;
sem_t t1;
sem_t t2;


void confi_port(){
    
    TRISD = 0x00;
    
    
}

void aviaoidle()
{
 while(1)
 {
     TRISBbits.RB5 = 0;
     PORTBbits.RB5 = 0;
     
     while(1)
     {
         PORTBbits.RB5=1;
         delay(1000);
         PORTBbits.RB5=0;
     }
     
 }
}

void led_1()
{
    
   PORTDbits.RD3 = 0;
  PORTDbits.RD6 = 0;
  PORTDbits.RD4 = 0;
  PORTDbits.RD0 = 0;
 
  while (1) {
    
    PORTDbits.RD3 = 1;
    //voando
    delay(5000);
    //pede pista
    sem_wait(&spista);
    //consegui pista 
    PORTDbits.RD3 = 0;
    //acende pista
    PORTDbits.RD6 = 1;
    //espera na pista
    delay(5000);
    
   //sai da pista
    PORTDbits.RD6 = 0;
    
    // libera pista
    sem_post(&spista); 
    delay(300);
    
    // vai para garagem
    PORTDbits.RD0 = 1;
    
    delay(5000);
    

    //pede pista pra voar
    sem_wait(&spista);
    //sai da garagem
    PORTDbits.RD0 = 0;
        
    //vai para pista
    PORTDbits.RD4 = 1;
    //espera
    delay(5000);
    //libera
    PORTDbits.RD4 = 0;
     
    sem_post(&spista);
    delay(400);

  }
}

void led_2()
{
    
     PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD4 = 0;
    PORTDbits.RD1 = 0;

    while(1)
    {
          
        PORTDbits.RD5 = 1;
        //voando
        delay(6000);
        //pede pista
        sem_wait(&spista);
        //consegui pista 
        PORTDbits.RD5 = 0;
        //acende pista
        PORTDbits.RD6 = 1;
        //espera na pista
        delay(6000);

       //sai da pista
        PORTDbits.RD6 = 0;

        // libera pista
        sem_post(&spista); 
        delay(300);
        // vai para garagem
        PORTDbits.RD1 = 1;
        delay(6000);
        //pede pista pra voar
        sem_wait(&spista);
        //sai da garagem
        PORTDbits.RD1 = 0;
        //vai para pista
        PORTDbits.RD4 = 1;
        //espera
        delay(6000);
        //libera
        PORTDbits.RD4 = 0;

        sem_post(&spista);
        

        
    }
}

void led_3()
{

  PORTDbits.RD7 = 0;
  PORTDbits.RD6 = 0;
  PORTDbits.RD4 = 0;
  PORTDbits.RD2 = 0;
 
  while (1) {

    PORTDbits.RD7 = 1;
    //voando
    delay(6000);
    //pede pista
    sem_wait(&spista);
    //consegui pista 
    PORTDbits.RD7 = 0;
    //acende pista
    PORTDbits.RD6 = 1;
    //espera na pista
    delay(6000);

   //sai da pista
    PORTDbits.RD6 = 0;
    
    // libera pista
    sem_post(&spista); 
    // vai para garagem
    
     //pipe_write(&testL, 't');
    PORTDbits.RD2 = 1;
    
    delay(6000);
    

    //pede pista pra voar
    sem_wait(&spista);
    //sai da garagem
    PORTDbits.RD2 = 0;

    //vai para pista
    PORTDbits.RD4 = 1;
    //espera
    delay(6000);
    //libera
    PORTDbits.RD4 = 0;
    
    sem_post(&spista);


  }


  
}


void dianoite()
{
    //create_pipe(&testL);
    while(1)
    {
       pipe_write(&testL, 't');
      //  write_pipe(&testL, 't');
        delay(1000);
    }
}

void acender()
{
    TRISCbits.RC5 = 0;
    PORTCbits.RC5 = 0;
    byte dado;
    LATCbits.LATC5 =0;
    
    while(1)
    {
     pipe_read(&testL, &dado);
     // dado= read_pipe(&testL);
     if(dado == 't')
     {
             //PORTDbits.RD4 = ~LATDbits.LATD4; 
                PORTCbits.RC5 = ~LATCbits.LATC5;
                delay(1000);
                //ORTCbits.RC5 = ~LATCbits.LATC5;
             //PORTDbits.RD4 = 0;
     }
    }
}