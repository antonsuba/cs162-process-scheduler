#ifndef _SJF_h
#define _SJF_h

using namespace std;

int currentTime = -1;
int index = -1;

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
        if(p1.arrival > currentTime){
            currentTime = p1.burstTime;
            index = p1.index;
            return false;
        }
        return (p1.burstTime > p2.burstTime) || p2.index == index;
    }
};

bool compareArrivalTime(Process p1, Process p2){
    return (p1.arrival < p2.arrival);
}

void fcfs(vector<Process> set){
    int size = set.size();
    int time = 0;

    sort(set.begin(), set.end(), compareArrivalTime);

    for(int i = 0; i < size; i++){
        if(set[i].arrival >= time){
            time = set[i].arrival;
        }

        cout << time << " " << set[i].index << " " << set[i].burstTime << "X" << endl;
        time+= set[i].burstTime;
    }
}

void sjf(vector<Process> set){
    int size = set.size();
    int time = 0;

    sort(set.begin(), set.end(), compareArrivalTime);

    priority_queue<Process, vector<Process>, SJFComparator> queue;
    
    for(int i = 0; i < size; i++){
        queue.push(set[i]);
    }

    while(!queue.empty()){
        Process p = queue.top();
        cout << time << " " << p.index << " " << p.burstTime << "X" << endl;

        time += p.burstTime;

        queue.pop();
    }
}

void srtf(vector<Process> set){
    int size = set.size();
    int time = 0;
    
    sort(set.begin(), set.end(), compareArrivalTime);

    for(int i = 0; i < size; i++){
        if(set[i].arrival > time){
            time = set[i].arrival;
        }
    }

}

#endif