/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <xc.h>
#include "kernel.h"
#include "tasks.h"
#include "memory.h"

asm("GLOBAL _task_idle, _aviao1, _aviao2, _ctpista");

sem_t semafaro;

void main(void) {
  
  setupOS();
  SRAMInitHeap();
  sem_init(&semafaro, 0);

  
  // Criar as tarefas
  create_task(2, 3, &ctpista);
  create_task(3, 3, &aviao1);
  create_task(4, 3, &aviao2);
  
   
  // Incializa o escalonador de tarefas
  start_os();
  
  
  // Teste (não precisa estar aqui)
  byte *mem = SRAMalloc(100);
  
  while (1);
  
  return;
}
