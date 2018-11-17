#include "semaphore.h"
#include "kernel.h"

extern u_int task_running;

void sem_init(sem_t *s, int value)
{
  di();
  
  s->contador = value;
  s->queue.s_queue_pos_in = 0;
  s->queue.s_queue_pos_out = 0;  
  
  ei();
}

void sem_wait(sem_t *s)
{
  di();
  
  // Decrementa o contador
  s->contador--;
  if (s->contador < 0) {
    s->queue.s_queue[s->queue.s_queue_pos_in] = task_running;
    s->queue.s_queue_pos_in = (s->queue.s_queue_pos_in + 1) % MAX_TASKS;
    dispatcher(WAITING);
  }
  
  ei();
}

void sem_post(sem_t *s)
{
  di();
  
  s->contador++;
  if (s->contador <= 0) {
    F_APTOS[s->queue.s_queue[s->queue.s_queue_pos_out]].task_state = READY;
    s->queue.s_queue_pos_out = (s->queue.s_queue_pos_out + 1) % s->queue.s_queue_pos_in;
    dispatcher(READY);
  }
  
  ei();  
}

int sem_get_value(sem_t s)
{
  return s.contador;
}

