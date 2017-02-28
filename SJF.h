#ifndef _SJF_h
#define _SJF_h

struct Process{
    int index;
    int arrival;
    int burstTime;
    int priority;

    Process(int index, int arrival, int burstTime, int priority){
        this->index = index;
        this->arrival = arrival;
        this->burstTime = burstTime;
        this->priority = priority;
    }
};

struct SJFComparator{

    
};

#endif