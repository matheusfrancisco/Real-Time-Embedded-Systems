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
//sem_t saviao2;
//sem_t saviao3;


sem_t spista;
///sem_init(&spista, 0);
//pista1.status = 0;

pipe_t pipeluzes;

void aviao1()
{
  TRISCbits.RC5 = 0;
  PORTCbits.RC5 = 0;
  
  TRISDbits.RD1 = 0;
  PORTDbits.RD1 = 0;
  
  TRISDbits.RD0 = 0;
  PORTDbits.RD0 = 0;
  
  
  
  
  u_int tempo_v1 = 5000;
  u_int tempo_p1 = 1000;
  
  
  //LCD_Init();
  //LCD_PutChar('a');
  
  while (1) {
    PORTDbits.RD1 = 1;
    delay(tempo_v1);
    
    sem_wait(&spista);
    //pista1->status = 1;
    PORTDbits.RD1 = 0;
    PORTCbits.RC5 = 1;
    
    
    
    delay(tempo_p1);
    //pista1->status = 0;
    PORTCbits.RC5 = 0;
    delay(2000);
    
    sem_post(&spista); 
    
    delay(600);
    sem_wait(&spista);
    
    PORTDbits.RD0 = 1;
    delay(5200);
    PORTDbits.RD0 = 0;
    delay(2500);
    sem_post(&spista);
    delay(2340);
   }
}

void aviao2()
{
  // TRISCbits.RC5 = 0;
  //PORTCbits.RC5 = 0;
  
  
  TRISDbits.RD2 = 0;
  PORTDbits.RD2 = 0;
  
  //TRISDbits.RD0 = 0;
  //PORTDbits.RD0 = 0;
  
  u_int tempo_p2 = 1000;
  u_int tempo_v2 = 6000;
  while (1) {
    PORTDbits.RD2 = 1;
      
    delay(tempo_v2);
    sem_wait(&spista);
    //pista1->status = 1;
    PORTDbits.RD2 = 0;
  
    PORTCbits.RC5 = 1;
    
    delay(tempo_p2);

    
    PORTCbits.RC5 = 0;
     delay(600);

    sem_post(&spista);    
    
    delay(600);
    sem_wait(&spista);
    
    PORTDbits.RD0 = 1;
    delay(4200);
    
    PORTDbits.RD0 = 0;
    delay(1250);
    sem_post(&spista);
    delay(2300);
   }
}
/*
void aviao3()
{
 //TRISCbits.RC5 = 0;
  //PORTCbits.RC5 = 0;
  
  TRISDbits.RD3 = 0;
  PORTDbits.RD3 = 0;
  
  
 // TRISDbits.RD0 = 0;
//  PORTDbits.RD0 = 0;
  
  u_int tempo_v = 7000;
  u_int tempo_p = 1000;
  
  
  while (1) {
    PORTDbits.RD3 = 1;
      
    delay(tempo_v);
    sem_wait(&spista);
    //pista1->status = 1;
    PORTDbits.RD3 = 0;
  
    PORTCbits.RC5 = 1;
    
    delay(tempo_p);
    //pista1->status = 0;
    
    PORTCbits.RC5 = 0;
    delay(600);
    sem_post(&spista);    
    
    
    delay(600);
    sem_wait(&spista);
    
    PORTDbits.RD0 = 1;
    delay(7500);
    PORTDbits.RD0 = 0;
    delay(1500);
    sem_post(&spista);
    delay(1000);
   }
}
*/
void tluzes()
{
  TRISDbits.RD6 = 0;
  PORTDbits.RD6 = 0;

//  byte dado;
//  dado = (byte*)SRAMalloc(sizeof(byte*) );
  
  while(1)
  {
    byte dado;
    dado = (byte*)SRAMalloc(sizeof(byte*) );
  
      dado = read_pipe(&pipeluzes);
      
      if (dado == 'a')
      {
          
           PORTDbits.RD6 = 1;
           delay(1000);
           PORTDbits.RD6 = 0;
 
      }
      SRAMfree(dado);
  }
    
}

void tluzesescreve()
{

  create_pipe(&pipeluzes);
  while(1)
  {
      delay(3000);
      write_pipe(&pipeluzes,'a');
      //delay(2000);
     // write_pipe(&pipeluzes,'b');
  }
    
}
