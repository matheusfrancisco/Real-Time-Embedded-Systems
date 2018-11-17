/**
 * Immortal Operating System - immortalOS 
 * 
 */

#ifndef PIPE_H
#define	PIPE_H
#include "types.h"

#define MAX_PIPE_SIZE 1

typedef struct pipe_bloqued_queue {
    u_int b_queue[MAX_TASKS];
    u_int b_queue_pos_in;
    u_int b_queue_pos_out;
} pipe_bloqued_queue_t;

typedef struct pipe {
    byte pipe_queue[MAX_PIPE_SIZE];
    //pipe_bloqued_queue_t pipe_bloqued;
    u_int pos_read_pipe;
    u_int pos_write_pipe;
    u_int pipe_itens;
    // Posição dos processos bloqueados
    u_int pos_bloqued_read;
    u_int pos_bloqued_write;    
} pipe_t;

void create_pipe(pipe_t *pipe);
void write_pipe(pipe_t *pipe, byte data);
byte read_pipe(pipe_t *pipe);


#endif	/* PIPE_H */

