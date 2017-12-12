
#include "copyright.h"
#include "multilevel.h"
#include "system.h"

Multilevel::Multilevel()
{
    readyListPQ = new List;
    readyListSJF = new List;
}

Multilevel::~Multilevel()
{
    delete readyListPQ;
    delete readyListSJF;
}

void
Multilevel::ReadyToRun (Thread *thread, int prio, bool sjflevel)
{
if(sjflevel){
    DEBUG('t', "Putting thread %s on sjf ready list.\n", thread->getName());

    thread->setStatus(READY);
    readyListSJF->SortedInsert((void *)thread, prio);
}else{
    DEBUG('t', "Putting thread %s on pq ready list.\n", thread->getName());

    thread->setStatus(READY);
    readyListPQ->SortedInsert((void *)thread, prio);

}
}

Thread *
Multilevel::FindNextToRun()
{
if(!readyListSJF->IsEmpty())
	{return (Thread *)readyListSJF->Remove();}
else
	{return (Thread *)readyListPQ->Remove();}
}


void
Multilevel::Run (Thread *nextThread)
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
Multilevel::Print()
{
    printf("sjf Ready list contents:\n");
    readyListSJF->Mapcar((VoidFunctionPtr) ThreadPrint);

    printf("pq Ready list contents:\n");
    readyListPQ->Mapcar((VoidFunctionPtr) ThreadPrint);
}