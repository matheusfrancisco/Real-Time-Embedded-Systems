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

void numerodeaviosG(){
    
    TRISB = 0x00;
    PORTB = 0x11;
    
    while(1)
    {
        //int a = sem_get_value(spista);
        
        if(cont == 1)
        {
            PORTBbits.RB0= 0;
            PORTBbits.RB1= 0;
            PORTBbits.RB2= 1;
            PORTBbits.RB3= 1;
            PORTBbits.RB4= 1;
            PORTBbits.RB5= 1;
            PORTBbits.RB6= 1;
        }
        delay(1000);
     
        if(cont == 2)
        {
            PORTBbits.RB0= 0;
            PORTBbits.RB1= 0;
            PORTBbits.RB2= 1;
            PORTBbits.RB3= 1;
            PORTBbits.RB4= 0;
            PORTBbits.RB5= 0;
            PORTBbits.RB6= 0;
        }
     
    }
}

void LCD_test()
{
    Lcd_Write_Char("a");
    di();
    __delay_ms(1000);
    ei();
}

void confi_port(){
    
    TRISD = 0x00;
    
    
}
/**
void aviao1()
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
    
    cont++;
    // vai para garagem
    PORTDbits.RD0 = 1;
    
    delay(5000);
    

    //pede pista pra voar
    sem_wait(&spista);
    //sai da garagem
    PORTDbits.RD0 = 0;
        
    cont--;
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
*/

/**
void aviao2()
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
        cont++;
        delay(6000);
        //pede pista pra voar
        sem_wait(&spista);
        //sai da garagem
        PORTDbits.RD1 = 0;
        cont--;
        //vai para pista
        PORTDbits.RD4 = 1;
        //espera
        delay(6000);
        //libera
        PORTDbits.RD4 = 0;

        sem_post(&spista);
        

        
    }
}

*/

/*
void aviao3()
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
    cont++;
    PORTDbits.RD2 = 1;
    
    delay(6000);
    

    //pede pista pra voar
    sem_wait(&spista);
    //sai da garagem
    PORTDbits.RD2 = 0;
cont--;
    //vai para pista
    PORTDbits.RD4 = 1;
    //espera
    delay(6000);
    //libera
    PORTDbits.RD4 = 0;
    
    sem_post(&spista);


  }
}
*/
void tluzes()
{
  TRISCbits.RC5 = 0;
  PORTCbits.RC5 = 0;


    byte dado;
 //PORTCbits.RC5 = 1;
  while(1)
  {
              dado = read_pipe(&pipeluzes);
      if (dado == 'l')
      {
          
           PORTCbits.RC5 = ~PORTCbits.RC5 ;
           delay(5000);
          
 
      }
        dado = 'n';
        if(dado =='n')
        {
                     PORTCbits.RC5 = ~PORTCbits.RC5 ;
           delay(5000);
           
        }
       //delay(3000);
  }
    
}

void tluzesescreve()
{
   
    create_pipe(&pipeluzes);
   
  while(1)
  {

            write_pipe(&pipeluzes, 'l'); 
     
      //write_pipe(&pipeluzes, 2);
      
   
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

    pipe_create(&testL ,4,1);
   
           
       
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
    
     pipe_write(&testL, 't');
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

void acender()
{
    TRISCbits.RC5 = 0;
    PORTCbits.RC5 = 0;
    byte dado;
    LATCbits.LATC5 =0;
    
    while(1)
    {
     pipe_read(&testL, &dado);
     if(dado == 't')
     {
             //PORTDbits.RD4 = ~LATDbits.LATD4; 
                PORTCbits.RC5 = ~LATCbits.LATC5;
                delay(1000);
                PORTCbits.RC5 = ~LATCbits.LATC5;
             //PORTDbits.RD4 = 0;
     }
    }
}

