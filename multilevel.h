#ifndef MULTILEVEL_H
#define MULTILEVEL_H


#include "copyright.h"
#include "list.h"
#include "thread.h"
#include "scheduler.h"

class Multilevel : Scheduler{
public:
    Multilevel();
    ~Multilevel();
    void ReadyToRun(Thread* thread, int prio, bool sjflevel);
    Thread* FindNextToRun();
    void Run(Thread* nextThread);
    void Print();
private:
    List *readyListPQ;
    List *readyListSJF;

};

#endif