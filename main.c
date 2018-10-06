/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include <xc.h>
#include "kernel.h"
#include "tasks.h"

asm("GLOBAL _task_idle, _task_one, _task_two, _task_thre");

void main(void) {
  
  setupOS();
  
  // Criar as tarefas
  create_task(2, 3, &task_one);
  create_task(3, 3, &task_two);
  create_task(4, 3, &task_thre);
  
  // Incializa o escalonador de tarefas
  start_os();
  
  while (1);
  
  return;
}
