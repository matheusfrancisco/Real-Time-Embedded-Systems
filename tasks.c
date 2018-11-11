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


void testlcd()
{
    while(1){
        
     int a ;
      
     a = sem_get_value(spista);
     
     
     if(a== 0){
     
   
    Lcd_Write_String("Pista OCUPADA");
    //delay(10000);
    //reset
           // => E = 0
   
    //delay(2000);
    //di();
    //    Lcd_Clear();
    //ei();
         for(int b=0;b<100000;b++)
         {
             int c;
             c = c +b;
         }
     }
     else{
            Lcd_Write_String("Pista Livre");
    //delay(10000);
    //reset
           // => E = 0
  
   //  delay(2000);
   // di();
   //     Lcd_Clear();
   // ei();
   
          for(int b=0;b<100000;b++)
         {
             int c;
             c = c +b;
         }
     }
    }
}
void aviao1()
{
    //led pista
  TRISCbits.RC5 = 0;
  PORTCbits.RC5 = 0;
  
  
  //led aviao 1
  TRISCbits.RC4 = 0;
  PORTCbits.RC4 = 0;
  
  TRISCbits.RC3 = 0;
  PORTCbits.RC3 = 0;
  
  
  u_int tempo_v1 = 5000;
  u_int tempo_p1 = 1000;
  
  //LCD_Init();
  //LCD_PutChar('a');
  
  while (1) {
    PORTCbits.RC4 = 1;
    delay(tempo_v1);
    
    //Lcd_Write_String("A");

    
    sem_wait(&spista);
   
    //pista1->status = 1;
    PORTCbits.RC4 = 0;
    PORTCbits.RC5 = 1;
    
    delay(5000);

    delay(tempo_p1);
    //pista1->status = 0;
    PORTCbits.RC5 = 0;
    delay(2000);
    
    sem_post(&spista); 
    
    delay(600);
    sem_wait(&spista);
    
    PORTCbits.RC3 = 1;
    delay(5200);
    PORTCbits.RC3 = 0;
    delay(2500);
    sem_post(&spista);
    delay(2340);
   }
}

void aviao2()
{
  // TRISCbits.RC5 = 0;
  //PORTCbits.RC5 = 0;
  
  //aviao 2
  TRISCbits.RC6 = 0;
  PORTCbits.RC6 = 0;
  
  //TRISDbits.RD0 = 0;
  //PORTDbits.RD0 = 0;
  
  u_int tempo_p2 = 1000;
  u_int tempo_v2 = 6000;
  while (1) {
    PORTCbits.RC6 = 1;
      
    delay(tempo_v2);
    sem_wait(&spista);
    //pista1->status = 1;
    PORTCbits.RC6 = 0;
  
    PORTCbits.RC5 = 1;
    
    delay(tempo_p2);

    
    PORTCbits.RC5 = 0;
     delay(600);

    sem_post(&spista);    
    
    delay(600);
    sem_wait(&spista);
    
    PORTCbits.RC3 = 1;
    delay(4200);
    
    PORTCbits.RC3 = 0;
    delay(1250);
    sem_post(&spista);
    delay(2300);
   }
}

void aviao3()
{
 //TRISCbits.RC5 = 0;
  //PORTCbits.RC5 = 0;
  //aviao3
  TRISCbits.RC7 = 0;
  PORTCbits.RC7 = 0;
  
  
 // TRISDbits.RD0 = 0;
//  PORTDbits.RD0 = 0;
  
  u_int tempo_v = 7000;
  u_int tempo_p = 1000;
  
  
  while (1) {
    PORTCbits.RC7 = 1;

    delay(tempo_v);
    sem_wait(&spista);
    //pista1->status = 1;
    PORTCbits.RC7 = 0;
  
    PORTCbits.RC5 = 1;
    delay(tempo_p);
    //pista1->status = 0;
    
    PORTCbits.RC5 = 0;
    delay(600);
    sem_post(&spista);    
    
    
    delay(600);
    sem_wait(&spista);
    
    PORTCbits.RC3 = 1;
    delay(7500);
    PORTCbits.RC3 = 0;
    delay(1500);
    sem_post(&spista);
    delay(1000);
   }
}
/*

void aviao4()
{
 //TRISCbits.RC5 = 0;
  //PORTCbits.RC5 = 0;
  
  TRISDbits.RD6 = 0;
  PORTDbits.RD6 = 0;
  
  
 // TRISDbits.RD0 = 0;
//  PORTDbits.RD0 = 0;
  
  u_int tempo_v = 7000;
  u_int tempo_p = 1000;
  
  
  while (1) {
    PORTDbits.RD6 = 1;
      
    delay(tempo_v);
    sem_wait(&spista);
    //pista1->status = 1;
    PORTDbits.RD6 = 0;
  
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


void tluzes()
{
  TRISDbits.RD6 = 0;
  PORTDbits.RD6 = 0;

      //  byte dado;
      //  dado = (byte*)SRAMalloc(sizeof(byte*) );
      byte dado;
       dado = (byte*)SRAMalloc(sizeof(byte*) );


  while(1)
  {
  
      dado = read_pipe(&mensagens);
      
      if (dado == 'A')
      {
          
           PORTDbits.RD6 = 1;
           delay(1000);
           PORTDbits.RD6 = 0;
 
      }
      //    SRAMfree(dado);
  }
    
}

void tluzesescreve()
{
    create_pipe(&mensagens, 4);
  byte dados[1] = {'A'};
  //u_int index_send = 0;
 // create_pipe(&pipeluzes);
  while(1)
  {
      delay(3000);
        //  write_pipe(&pipeluzes,'a');
      write_pipe(&mensagens, 'A');
      
      //delay(2000);
     // write_pipe(&pipeluzes,'b');
  }
    
}*/