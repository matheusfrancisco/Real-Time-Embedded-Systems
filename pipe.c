/**
 * Immortal Operating System - immortalOS
 * 
 */


#include "pipe.h"
#include "kernel.h"
#include "config.h"
#include "types.h"
#include "memory.h"


extern u_int tasks_installed;
/*
void create_pipe(pipe_t *pipe)
{
  pipe->pos_read_pipe = 0;
  pipe->pos_write_pipe = 0;
  pipe->pipe_itens = 0;
  pipe->pos_bloqued_read = 0;
  pipe->pos_bloqued_write = 0;
}

void write_pipe(pipe_t *pipe, byte data)
{
  di();
  
  // Verifica se o PIPE está cheio
  if (pipe->pipe_itens == MAX_PIPE_SIZE) {
  
    pipe->pos_bloqued_write = task_running;
     dispatcher(WAITING_PIPE);
  }

  pipe->pipe_queue[pipe->pos_write_pipe] = data;
  pipe->pos_write_pipe = (pipe->pos_write_pipe + 1) % MAX_PIPE_SIZE;
  pipe->pipe_itens++;
  
  // Desbloqueia leitor, caso tenha algum bloqueado
  if (pipe->pos_bloqued_read > 0) {
    F_APTOS[pipe->pos_bloqued_read].task_state = READY;
    pipe->pos_bloqued_read = 0;
    #if PRIOR_SCH
    dispatcher(READY);
    #endif
  ei();

  }

  
  ei();
}

byte read_pipe(pipe_t *pipe)
{
    di();
    byte dado;

  // Verifica se o PIPE está vazio
  if (pipe->pipe_itens == 0) {
    //pipe->pipe_bloqued.b_queue[pipe->pipe_bloqued.b_queue_pos_in] = task_running;
    //pipe->pipe_bloqued.b_queue_pos_in = (pipe->pipe_bloqued.b_queue_pos_in+1) % MAX_TASKS;
    pipe->pos_bloqued_read = task_running;
    dispatcher(WAITING_PIPE);
  }
  
  dado = pipe->pipe_queue[pipe->pos_read_pipe];
  pipe->pos_read_pipe = (pipe->pos_read_pipe + 1) % MAX_PIPE_SIZE;
  pipe->pipe_itens--;

  // Desbloquear o escritor
  if (pipe->pos_bloqued_write > 0) {
    F_APTOS[pipe->pos_bloqued_write].task_state = READY;
    pipe->pos_bloqued_write = 0;
    #if PRIOR_SCH
    dispatcher(READY);
    #endif
  }
  
   ei();
  
  return dado;
}
 * 
 */


/*
 * Chamadas de sistema para manipulação do PIPE
 */
void pipe_create(pipe_t *pipe_handler, u_int id, u_int size)
{
  pipe_handler->p_id        = id;
  pipe_handler->p_pos_read  = 0;
  pipe_handler->p_pos_write = 0;
  pipe_handler->p_size      = size;
  pipe_handler->p_msg_queue = SRAMalloc(size); 
  pipe_handler->p_count     = 0;
}

void pipe_read(pipe_t *pipe_handler, char* msg)
{
  di();
  
  if (pipe_handler->p_count == 0) { // PIPE está vazio
    // Bloqueia processo que tentou ler
    // Chama o despachante
    dispatcher(WAITING_PIPE);
  }
  else {
    *msg = pipe_handler->p_msg_queue[pipe_handler->p_pos_read];
    pipe_handler->p_pos_read = (pipe_handler->p_pos_read + 1) % pipe_handler->p_size;
    pipe_handler->p_count--;
    // Desbloqueia processos que estão aguardando espaço no pipe
    libera_processos();
  }
  
  ei();
}

void pipe_write(pipe_t *pipe_handler, char msg)
{
  di();
  
  if (pipe_handler->p_count == pipe_handler->p_size) { // PIPE está cheio
    // Bloqueia processo que tentou ler
    // Chama o despachante
    dispatcher(WAITING_PIPE);
  }
  else {
    pipe_handler->p_msg_queue[pipe_handler->p_pos_write] = msg;
    pipe_handler->p_pos_write = (pipe_handler->p_pos_write + 1) % pipe_handler->p_size;
    pipe_handler->p_count++;
    // Desbloqueia processo que querem ler do pipe
    libera_processos();
  }

  ei();  
}

void pipe_destroy(pipe_t *pipe_handler)
{
  SRAMfree(pipe_handler->p_msg_queue);
}

void libera_processos()
{
  int i;
  for (i = 0; i < tasks_installed; i++)
    if (F_APTOS[i].task_state == WAITING_PIPE)
      F_APTOS[i].task_state = READY;
}