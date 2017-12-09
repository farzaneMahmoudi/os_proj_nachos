#ifndef PRIORITY_H
#define PRIORITY_H


#include "copyright.h"
#include "list.h"
#include "thread.h"

class Priority {
public:
    Priority();
    ~Priority();
    void ReadyToRun(Thread* thread, int prio);
    Thread* FindNextToRun();
    void Run(Thread* nextThread);
    void Print();
private:
    List *readyList;

};

#endif