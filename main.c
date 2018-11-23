/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <xc.h>
#include "kernel.h"
#include "tasks.h"
#include "memory.h"
#include "pipe.h"
#include "lcd.h"

//asm("GLOBAL _task_idle ,_aviao1, _aviao2, _aviao3 ,_tluzesescreve, _tluzes"); 
asm("GLOBAL   _aviaoidle , _led_1, _led_2, _led_3,_dianoite, _acender"); 

//extern pipe_t mensagens;

void main(void) {
  
  setupOS();
  SRAMInitHeap();
  extern sem_t spista;
  extern sem_t t1;
  extern sem_t t2;
  extern pipe_t testL;
  TRISBbits.RB0 = 0;
    
  
  confi_port();
  sem_init(&spista, 1);
  sem_init(&t1, 1);
  pipe_create(&testL,5,1);

  //sem_init(&t2, 1);


  // Criar as tarefas
  create_task(1, 3, &aviaoidle);

  create_task(2, 3, &led_1);
  create_task(3, 3, &led_2);
  create_task(4, 3, &led_3);
  
  create_task(5, 3, &dianoite);
  create_task(6, 3, &acender);

 
  //create_task(2, 3, &aviao1);
  //create_task(3, 3, &aviao2);
  //create_task(4, 3, &aviao3);

  //create_task(7, 3, &aviao4);
  //create_task(5, 3, &tluzesescreve);
  //create_task(6, 3, &tluzes);
  //create_task(8,3,&LCD_test);

  //sem_init(&spista, 1);
  
 
  //sem_init(&spista,0);  
  // Incializa o escalonador de tarefas
  //start_os();
  
  
  // Teste (não precisa estar aqui)
  //byte *mem = SRAMalloc(100);
  start_os();
  while (1)
  {
      
  }
  
  return;
}
