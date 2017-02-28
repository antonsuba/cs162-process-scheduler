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

    int currentTime;
    int index;

    bool operator()(const Process &p1, const Process &p2)
    { 
        if(p1.arrival >= currentTime){
            currentTime = p1.burstTime;
            index = p1.index;
            return false;
        }
        return (p1.burstTime < p2.burstTime) || p2.index == index;
    }
};

#endif