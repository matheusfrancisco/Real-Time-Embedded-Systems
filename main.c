/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <xc.h>
#include "kernel.h"
#include "tasks.h"
#include "memory.h"

asm("GLOBAL _task_idle, _aviao2, _aviao3, _ctpista");

void main(void) {
  
  setupOS();
  
  // Criar as tarefas
  create_task(2, 3, &ctpista);
  create_task(3, 3, &aviao2);
  create_task(4, 3, &aviao3);
  
   
  // Incializa o escalonador de tarefas
  start_os();
  
  
  // Teste (não precisa estar aqui)
  byte *mem = SRAMalloc(100);
  
  while (1);
  
  return;
}
