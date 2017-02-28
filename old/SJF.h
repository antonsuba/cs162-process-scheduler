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

    bool operator()(const Process &p1, const Process &p2) const
    { 
        if(p1.arrival >= p2.arrival){
            return p1.burstTime > p2.burstTime;
        }
        return p1.arrival > p2.arrival;
    }
};

#endif