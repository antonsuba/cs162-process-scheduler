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

bool compareArrivalTime(Process p1, Process p2){
    return (p1.arrival < p2.arrival);
}

void fcfs(std::vector<Process> set){
    //int size = sizeof(set)/sizeof(set[0]);
    int size = set.size();
    int time = 0;

    std::sort(set.begin(), set.end(), compareArrivalTime);

    for(int i = 0; i < size; i++){
        if(set[i].arrival >= time){
            time = set[i].arrival;
        }

        std::cout << time << " " << set[i].index << " " << set[i].burstTime << std::endl;
        time+= set[i].burstTime;
    }
}

void srtf(std::vector<Process> set){
    int size = set.size();
    int time = 0;
    
}

#endif