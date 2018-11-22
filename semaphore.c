#include "semaphore.h"
#include "kernel.h"
#include "types.h"
#include "memory.h"

extern u_int task_running;

void sem_init(sem_t *s, int value)
{
  di();
  
  s->contador = value;
  s->queue.task = (u_int*)SRAMalloc(sizeof(u_int)*MAX_TASKS);
  s->queue.first = 0;
  s->queue.size = 0;  
  
  ei();
}

void sem_wait(sem_t *s)
{
  di();
  u_int task_pos = 0;
  // Decrementa o contador
  s->contador--;
  if (s->contador < 0) {
    u_int pos = (s->queue.size + s->queue.first) % MAX_TASKS; 
    s->queue.task[pos] = task_running;
    s->queue.size++;
    //s->queue.s_queue[s->queue.s_queue_pos_in] = task_running;
    //s->queue.s_queue_pos_in = (s->queue.s_queue_pos_in + 1) % MAX_TASKS;
    dispatcher(WAITING);
  }
  
  ei();
}

void sem_post(sem_t *s)
{
  di();
  
  s->contador++;
  if (s->contador <= 0) {
      u_int value = s->queue.task[s->queue.first];
      s->queue.first = (s->queue.first + 1) % MAX_TASKS;
      s->queue.size--;
      F_APTOS[value].task_state = READY;
    //F_APTOS[s->queue.s_queue[s->queue.s_queue_pos_out]].task_state = READY;
    //s->queue.s_queue_pos_out = (s->queue.s_queue_pos_out + 1) % s->queue.s_queue_pos_in;
    dispatcher(READY);
  }
  
  ei();  
}

int sem_get_value(sem_t s)
{
  return s.contador;
}

