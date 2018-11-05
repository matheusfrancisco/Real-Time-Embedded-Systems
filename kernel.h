/**
 * Immortal Operating System - immortalOS 
 * 
 */

#ifndef KERNEL_H
#define	KERNEL_H

#include "types.h"

extern tcb_t F_APTOS[MAX_TASKS];
extern u_int task_running;

void create_task(u_int id, u_int prior, f_ptr task_f);
u_int get_id(u_int task_ptr);
void delay(u_int time_ms);
void dispatcher(state_t state);
void task_idle();
void setupOS();
void interrupt int_high();
void start_os();

// Macros para salvamento de contexto
//di();

#define SAVE_CONTEXT(STATE) \    
    F_APTOS[task_running].task_state = STATE; \
    F_APTOS[task_running].BSR_register = BSR; \
    F_APTOS[task_running].STATUS_register = STATUS; \
    F_APTOS[task_running].WORK_register = WREG; \
    F_APTOS[task_running].task_stack.stack_size = 0; \
    do { \\
      F_APTOS[task_running].task_stack.STACK[F_APTOS[task_running].task_stack.stack_size].TOSU_register = TOSU; \
      F_APTOS[task_running].task_stack.STACK[F_APTOS[task_running].task_stack.stack_size].TOSL_register = TOSL; \
      F_APTOS[task_running].task_stack.STACK[F_APTOS[task_running].task_stack.stack_size].TOSH_register = TOSH; \
      F_APTOS[task_running].task_stack.stack_size++; \
      asm("POP");\      
    } while (STKPTR);
    
            
#define RESTORE_CONTEXT()\\
    STKPTR = 0;\\    
    if (F_APTOS[task_running].task_stack.stack_size == 0) {\\
      asm("PUSH");\\
      TOS = F_APTOS[task_running].task_f;\\
    }\\            
    else {\\
        BSR = F_APTOS[task_running].BSR_register;\\
        STATUS = F_APTOS[task_running].STATUS_register;\\
        WREG = F_APTOS[task_running].WORK_register;\\    
        do { \\
          asm("PUSH");\\
          F_APTOS[task_running].task_stack.stack_size--;\\  
          TOSU = F_APTOS[task_running].task_stack.STACK[F_APTOS[task_running].task_stack.stack_size].TOSU_register;\\
          TOSL = F_APTOS[task_running].task_stack.STACK[F_APTOS[task_running].task_stack.stack_size].TOSL_register;\\      
          TOSH = F_APTOS[task_running].task_stack.STACK[F_APTOS[task_running].task_stack.stack_size].TOSH_register;\\
        } while (F_APTOS[task_running].task_stack.stack_size);\\            
    }\\
    F_APTOS[task_running].task_state = RUNNING;\
            
#endif	/* KERNEL_H */

