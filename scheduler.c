/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include "scheduler.h"


extern u_int tasks_installed;
extern u_int task_running;
extern tcb_t F_APTOS[MAX_TASKS];

u_int contagemR()
{
    u_int x = 0;
    for (int i = 1; i < MAX_TASKS ; i++)
    {
        if (F_APTOS[i].task_state == READY) x++;
    }
    return x;
}

u_int rr_scheduler()
{
  u_int next_task_to_run = 0;
  u_int j = task_running;
  u_int cont = contagemR();
  
  PORTBbits.RB0 = ~LATBbits.LATB0;

  do {
      j++;
    next_task_to_run = (j) % tasks_installed;    
  } while (F_APTOS[next_task_to_run].task_state != READY || (cont>0 && next_task_to_run == 0));
  
  return next_task_to_run;
}

u_int prior_scheduler()
{
  u_int next_task_to_run = 0, i;
    PORTBbits.RB0 = ~LATBbits.LATB0;

  for (i = 1; i < tasks_installed; i++) {
    if (F_APTOS[next_task_to_run].task_prior > F_APTOS[i].task_prior) {
      if (F_APTOS[i].task_state == READY)
        next_task_to_run = i; 
    }
  }
  
  return next_task_to_run;
}
