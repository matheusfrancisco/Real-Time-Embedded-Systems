/**
 * Immortal Operating System - immortalOS 
 * 
 */

#ifndef TASKS_H
#define	TASKS_H

#include "semaphore.h"

typedef struct aviao{
    u_int numero;
    u_int tempo_v;
    u_int tempo_p;
}aviao_t;

typedef struct pista{
    aviao_t aviaozinho;
    u_int status;
    sem_t s;

}pista_t;

aviao_t createAviao(aviao_t *av, u_int tempo_v, u_int tempo_p, u_int numero );
void aviao1();
void aviao2();
void ctpista();

#endif	/* TASKS_H */

