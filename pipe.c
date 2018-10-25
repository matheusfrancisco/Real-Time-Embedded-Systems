/**
 * Immortal Operating System - immortalOS
 * 
 */

#include "pipe.h"
#include "kernel.h"
#include "config.h"

void create_pipe(pipe_t *pipe)
{
  pipe->pos_read_pipe = 0;
  pipe->pos_write_pipe = 0;
  pipe->pipe_itens = 0;
  //pipe->pipe_bloqued.b_queue_pos_in = 0;
  //pipe->pipe_bloqued.b_queue_pos_out = 0;
  pipe->pos_bloqued_read = 0;
  pipe->pos_bloqued_write = 0;
}

void write_pipe(pipe_t *pipe, byte data)
{
  di();
  
  // Verifica se o PIPE está cheio
  if (pipe->pipe_itens == MAX_PIPE_SIZE) {
    //pipe->pipe_bloqued.b_queue[pipe->pipe_bloqued.b_queue_pos_in] = task_running;
    pipe->pos_bloqued_write = task_running;
    //pipe->pipe_bloqued.b_queue_pos_in = (pipe->pipe_bloqued.b_queue_pos_in+1) % MAX_TASKS;
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
  }

  
  ei();
}

byte read_pipe(pipe_t *pipe)
{
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
  
  return dado;
}
