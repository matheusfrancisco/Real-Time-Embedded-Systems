/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <xc.h>
#include "kernel.h"
#include "tasks.h"
#include "memory.h"

asm("GLOBAL _task_idle, _task_one, _task_two, _task_thre");

void main(void) {
  
  setupOS();
  
  // Criar as tarefas
  create_task(2, 3, &task_one);
  create_task(3, 3, &task_two);
  create_task(4, 3, &task_thre);
  
   
  // Incializa o escalonador de tarefas
  start_os();
  
  
  // Teste (não precisa estar aqui)
  byte *mem = SRAMalloc(100);
  
  while (1);
  
  return;
}
