/**
 * Immortal Operating System - immortalOS 
 * 
 */

#ifndef TYPES_H
#define	TYPES_H

#include <xc.h>

//#define STACK_SIZE 31
const int STACK_SIZE = 31;
#define MAX_TASKS 10

#define ei() INTCONbits.GIE = 1
#define di() INTCONbits.GIE = 0

typedef unsigned int u_int;
typedef unsigned char byte;
typedef void(*f_ptr)(void);

typedef enum {READY = 1, RUNNING, SLEEPING, WAITING, WAITING_PIPE, FINISHED} state_t;

typedef struct stack_data {
  byte TOSU_register;
  byte TOSL_register;
  byte TOSH_register;
} stack_data_t;

typedef struct stack {
  stack_data_t STACK[STACK_SIZE];
  u_int stack_size;  
} stack_t;

typedef struct tcb {
  // Parâmetros da tarefa
  u_int task_id;
  u_int task_prior;
  f_ptr *task_f;
  u_int delay_time;
  // Dados do contexto da tarefa
  state_t task_state;  
  stack_t task_stack;
  byte BSR_register;
  byte STATUS_register;
  byte WORK_register;

} tcb_t;

#endif	/* TYPES_H */

