#include "copyright.h"
#include "scheduler.h"
#include "system.h"

ShortestJobFirst::ShortestJobFirst()
{ 
    readyList = new List; 

    int i;
    for(i=0; i<MAX_THREAD_COUNT; ++i) {
        cpu_count[i] = 0;
    }
} 


Scheduler::~Scheduler()
{ 
    delete readyList; 
} 

void
Scheduler::ReadyToRun (Thread *thread)
{
    thread->setStatus(READY);
    thread->wait_time_start = stats->totalTicks;
    if(thread->cpu_burst_previous >0 ){
        
        double estimate = alpha*thread->cpu_burst_previous 
                        + ( 1- alpha )*thread->cpu_burst_estimate;

        
        if(thread->cpu_burst_previous > 0) {
            int error;
            error = thread->cpu_burst_previous - estimate;
            if (error < 0 ) {
                error = error * -1;
            }

            stats->estimate_error += error;
        }

        thread->cpu_burst_estimate = estimate;
        readyList->SortedInsert((void *)thread, estimate);
    } else {
        readyList->Append((void *)thread);
}

Thread *Scheduler::FindNextToRun ()
{
	int key;
	return (Thread *)readyList->SortedRemove(&key);    
}

void
Scheduler::Run (Thread *nextThread)
{
    Thread *oldThread = currentThread;
    
#ifdef USER_PROGRAM			
    if (currentThread->space != NULL) {	
        currentThread->SaveUserState(); 
	currentThread->space->SaveState();
    }
#endif
    
    oldThread->CheckOverflow();		    
					  
    oldThread->total_time += stats->totalTicks - oldThread->start_time;

    currentThread = nextThread;		    
    currentThread->setStatus(RUNNING);    
  
    nextThread->cpu_burst_start = stats->totalTicks;
    nextThread->start_time = stats->totalTicks;
    nextThread->wait_time += stats->totalTicks - nextThread->wait_time_start;

    _SWITCH(oldThread, nextThread);


    if (threadToBeDestroyed != NULL) {
        delete threadToBeDestroyed;
	threadToBeDestroyed = NULL;
    }
    
#ifdef USER_PROGRAM
    if (currentThread->space != NULL) {
        currentThread->RestoreUserState();     
	currentThread->space->RestoreState();
    }
#endif
}


void
Scheduler::Print()
{
    printf("Ready list :\n");
    readyList->Mapcar((VoidFunctionPtr) ThreadPrint);
}
