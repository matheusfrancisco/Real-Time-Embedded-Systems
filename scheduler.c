/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include "scheduler.h"

extern u_int tasks_installed;
extern u_int task_running;
extern tcb_t F_APTOS[MAX_TASKS];

u_int rr_scheduler()
{
  u_int next_task_to_run = task_running;
  
  do {
    next_task_to_run = (next_task_to_run + 1) % tasks_installed;    
  } while (F_APTOS[next_task_to_run].task_state != READY);
  
  return next_task_to_run;
}

u_int prior_scheduler()
{
  u_int next_task_to_run = 0, i;
  
  for (i = 1; i < tasks_installed; i++) {
    if (F_APTOS[next_task_to_run].task_prior > F_APTOS[i].task_prior) {
      if (F_APTOS[i].task_state == READY)
        next_task_to_run = i; 
    }
  }
  
  return next_task_to_run;
}
