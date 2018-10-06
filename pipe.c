/**
 * Immortal Operating System - immortalOS 
 * 
 */

#include "pipe.h"
#include "kernel.h"

void create_pipe(pipe_t *pipe)
{
    pipe->pos_read_pipe = 0;
    pipe->pos_write_pipe = 0;
    pipe->pipe_bloqued.b_queue_pos_in = 0;
    pipe->pipe_bloqued.b_queue_pos_out;
    pipe->pipe_items = 0;
}
void write_pipe(pipe_t *pipe, byte data)
{
  di();
  
    if( pipe->pipe_items    == MAX_PIPE_SIZE )
    {
            pipe->pipe_bloqued.b_queue[pipe->pipe_bloqued.b_queue_pos_in] = task_running;
            pipe->pipe_bloqued.b_queue_pos_in = ((pipe->pipe_bloqued.b_queue_pos_in + 1) % MAX_TASKS);
            dispatcher(WAITING_PIPE);
    }else{
   
    pipe->pipe_queue[pipe->pos_write_pipe] = data;
    pipe->pos_write_pipe = ((pipe->pos_write_pipe + 1) % MAX_PIPE_SIZE);
    pipe->pipe_items++;
    
    for (int i = 0; i < 4; i++)
    if (F_APTOS[i].task_state == WAITING_PIPE)
      F_APTOS[i].task_state = READY;
    }

  ei();
}

byte read_pipe(pipe_t *pipe)
{
  byte dado;
  
    if (pipe->pipe_items == 0) {
        pipe->pipe_bloqued.b_queue[pipe->pipe_bloqued.b_queue_pos_in] = task_running;
        pipe->pipe_bloqued.b_queue_pos_in = (pipe->pipe_bloqued.b_queue_pos_in + 1) % MAX_TASKS;
        dispatcher(WAITING_PIPE);
    }
    else{

    dado = pipe->pipe_queue[pipe->pos_read_pipe];
    pipe->pos_read_pipe = (pipe->pos_read_pipe + 1) % MAX_PIPE_SIZE;
    pipe->pipe_items--;
    
    for (int i = 0; i < 4; i++)
    if (F_APTOS[i].task_state == WAITING_PIPE)
      F_APTOS[i].task_state = READY;
    }

    
  return dado;
}
