/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <xc.h>
#include "kernel.h"
#include "tasks.h"
#include "memory.h"

asm("GLOBAL _task_idle, _aviao1,_aviao2, _tluzesescreve, _tluzes"); 
extern sem_t spista;
extern sem_t saviao1;

void main(void) {
  
  setupOS();
  sem_init(&spista, 1);
  //LCD_Init();
  // Criar as tarefas
  create_task(1, 3, &aviao1);
  create_task(5, 3, &aviao2);
  //create_task(6, 3, &aviao3);
  create_task(2, 3, &tluzesescreve);
  create_task(3, 3, &tluzes);
  

  //sem_init(&spista, 1);
  
 
  //sem_init(&spista,0);  
  // Incializa o escalonador de tarefas
  start_os();
  
  
  // Teste (não precisa estar aqui)
  //byte *mem = SRAMalloc(100);
  
  while (1);
  
  return;
}
