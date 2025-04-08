#include "signal.h"

void
send_signal(int signal)
{
    struct proc *p;

    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
        if(p->pid > 2){
            if(signal == SIGINT){
                p->killed = 1;
            } else if(signal == SIGBG){
                p->suspended = 1;  // Add a new field
            } else if(signal == SIGFG){
                if(p->suspended){
                    p->suspended = 0;
                    p->state = RUNNABLE;
                }
            }
        }
    }
    release(&ptable.lock);
}
