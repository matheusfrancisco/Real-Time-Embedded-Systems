/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <xc.h>
#include "kernel.h"
#include "tasks.h"
#include "memory.h"
#include "pipe.h"

asm("GLOBAL _task_idle, _aviao1, _aviao2, _aviao3, _testlcd");// ,_tluzesescreve, _tluzes"); 
extern sem_t spista;
extern sem_t saviao1;
//extern pipe_t mensagens;

void main(void) {
  
  setupOS();
  SRAMInitHeap();
  
  sem_init(&spista, 1);
  


  // Criar as tarefas
  create_task(1, 3, &aviao1);
  create_task(2, 1, &aviao2);
  //create_task(3, 2, &aviao3);
  create_task(4, 4, &testlcd);

  //create_task(7, 3, &aviao4);
  //create_task(2, 3, &tluzesescreve);
  //create_task(3, 3, &tluzes);
  

  //sem_init(&spista, 1);
  
 
  //sem_init(&spista,0);  
  // Incializa o escalonador de tarefas
  start_os();
  
  
  // Teste (não precisa estar aqui)
  //byte *mem = SRAMalloc(100);
  
  while (1);
  
  return;
}
