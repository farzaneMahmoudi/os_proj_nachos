
#include "copyright.h"
#include "priority.h"
#include "system.h"

Priority::Priority()
{
    readyList = new List;
}


Priority::~Priority()
{
    delete readyList;
}


void
Priority::ReadyToRun (Thread *thread, int prio)
{
    DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());

    thread->setStatus(READY);
    readyList->SortedInsert((void *)thread, prio);
}


Thread *
Priority::FindNextToRun()
{
    return (Thread *)readyList->Remove();
}


void
Priority::Run (Thread *nextThread)
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
Priority::Print()
{
    printf("Ready list contents:\n");
    readyList->Mapcar((VoidFunctionPtr) ThreadPrint);
}