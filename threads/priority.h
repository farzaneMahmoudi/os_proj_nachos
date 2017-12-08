#include "scheduler.h"

class Priority : Scheduler {
public:
    void ReadyToRun(Thread* thread, int priority);
    Thread* FindNextToRun();
    void Run(Thread* nextThread);
    void Print();
private:
    List *readyList;

};

