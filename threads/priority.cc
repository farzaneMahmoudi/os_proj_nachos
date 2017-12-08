#include "copyright.h"
#include "priority.h"
#include "system.h"

void
Priority::ReadyToRun (Thread *thread, int priroty)
{
    DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());

    thread->setStatus(READY);
    readyList->SortedInsert((void *)thread, priroty);
}
