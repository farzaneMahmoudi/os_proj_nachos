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
ShortestJobFirst::ReadyToRun (Thread *thread)
{
    thread->setStatus(READY);
    readyList->Append((void *)thread);
}

Thread *ShortestJobFirst::FindNextToRun ()
{
	int key;
	return (Thread *)readyList->SortedRemove(&key);    
}

void
ShortestJobFirst::Run (Thread *nextThread)
{
    Thread *oldThread = currentThread;
    
    
    oldThread->CheckOverflow();		    
					  
}


void
ShortestJobFirst::Print()
{
    printf("Ready list :\n");
    readyList->Mapcar((VoidFunctionPtr) ThreadPrint);
}
