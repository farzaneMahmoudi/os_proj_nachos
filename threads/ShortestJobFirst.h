#ifndef SJF_H
#define SJF_H

#include "copyright.h"
#include "list.h"
#include "thread.h"
#include "scheduler.h"

class ShortestJobFirst : Scheduler {
  public:
    ShortestJobFirst();			
    ~ShortestJobFirst();			

    void ReadyToRun(Thread* thread, int prio);	
    Thread* FindNextToRun();		
					
    void Run(Thread* nextThread);	
    void Print();			

  private:
    List *readyList;  		
				
};

#endif // SJF_H
