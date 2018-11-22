/**
 * Immortal Operating System - immortalOS 
 * 
 */

#ifndef SEMAPHORE_H
#define	SEMAPHORE_H

#include "types.h"

typedef struct sem_queue {
    u_int s_queue[MAX_TASKS];
    u_int s_queue_pos_in;
    u_int s_queue_pos_out;
} sem_queue_t;

typedef struct _queue{
    u_int *task;
    u_int size;
    u_int first;
}queue_sem_t;

typedef struct sem {
    int contador;
    //sem_queue_t queue;
    queue_sem_t queue;
} sem_t;

void sem_init(sem_t *s, int value);
void sem_wait(sem_t *s);
void sem_post(sem_t *s);
int sem_get_value(sem_t s);

#endif	/* SEMAPHORE_H */

