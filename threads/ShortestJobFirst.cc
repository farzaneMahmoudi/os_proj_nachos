#include "copyright.h"
#include "ShortestJobFirst.h"
#include "system.h"

ShortestJobFirst::ShortestJobFirst()
{ 
    readyList = new List;
} 


ShortestJobFirst::~ShortestJobFirst()
{ 
    delete readyList; 
} 

void
ShortestJobFirst::ReadyToRun (Thread *thread, int prio)
{
    DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());

    thread->setStatus(READY);
    readyList->SortedInsert((void *)thread, prio);
}

Thread *ShortestJobFirst::FindNextToRun ()
{
	return (Thread *)readyList->Remove();   
}

void
ShortestJobFirst::Run (Thread *nextThread)
{
    Thread *oldThread = currentThread;

#ifdef USER_PROGRAM
    if (currentThread->space != NULL) {
        currentThread->SaveUserState();
	currentThread->space->SaveState();
    }
#endif

    oldThread->CheckOverflow();

    currentThread = nextThread;
    currentThread->setStatus(RUNNING);

    DEBUG('t', "Switching from thread \"%s\" to thread \"%s\"\n",
          oldThread->getName(), nextThread->getName());


    SWITCH(oldThread, nextThread);

    DEBUG('t', "Now in thread \"%s\"\n", currentThread->getName());


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
ShortestJobFirst::Print()
{
    printf("Ready list :\n");
    readyList->Mapcar((VoidFunctionPtr) ThreadPrint);
}
