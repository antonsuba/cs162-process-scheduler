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

bool compareShortestRemaining(Process p1, Process p2){
    return (p1.arrival <= p2.arrival && p1.burstTime < p2.burstTime);
}

bool comparePriority(Process p1, Process p2){
    return (p1.arrival <= p2.arrival && p1.priority < p2.priority);
}

void fcfs(std::vector<Process> set){
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
    sort(set.begin(), set.end(), compareShortestRemaining);

    for(int i = 0; i < size; i++){
        if(set[i].burstTime > 0){
            if(set[i].arrival > time){
                time = set[i].arrival;
            }

            std::sort(set.begin(), set.end(), compareShortestRemaining);
            
            /*std::cout << std::endl;
            std::cout << "SET:" << std::endl;
            for(int j = 0; j < size; j++){
                std::cout << set[j].index << " " << set[j].arrival << " " << set[j].burstTime << " " << set[j].priority << std::endl;
            }
            std::cout << "TIME: " << time << std::endl;
            std::cout << std::endl;*/

            int index = i;
            int runTime = 0;

            if(time < set[i+1].arrival && set[i+1].arrival < time + set[i].burstTime && set[i+1].burstTime < set[i].burstTime){
                runTime = set[i+1].arrival - time;
                i--;
            } else{
                runTime = set[i].burstTime;
                for(int j = i; j < size; j++){
                    if(set[j].arrival < time + set[i].burstTime && time + set[j].burstTime < time + set[i].burstTime){
                        runTime = set[j].arrival - time;
                        i--;
                        break;
                    }
                }
            }

            set[index].burstTime -= runTime;
            set[index].arrival += runTime;

            for(int k = i; k < size; k++){
                if(set[k].arrival < time + runTime && k != i){
                    set[k].arrival = time + runTime;
                }
            }

            if(set[index].burstTime > 0){
                std::cout << time << " " << set[index].index << " " << runTime << std::endl;
            } else{
                std::cout << time << " " << set[index].index << " " << runTime << "X" << std::endl;
            }

            time += runTime;
        }
    }

}

void p(std::vector<Process> set){
    int size = set.size();
    int time = 0;

    std::sort(set.begin(), set.end(), compareArrivalTime);
    std::sort(set.begin(), set.end(), comparePriority);

    for(int i = 0; i < size; i++){
        if(set[i].burstTime > 0){
            if(set[i].arrival > time){
                time = set[i].arrival;
            }

            std::sort(set.begin(), set.end(), comparePriority);
            
            /*std::cout << std::endl;
            std::cout << "SET:" << std::endl;
            for(int j = 0; j < size; j++){
                std::cout << set[j].index << " " << set[j].arrival << " " << set[j].burstTime << " " << set[j].priority << std::endl;
            }
            std::cout << "TIME: " << time << std::endl;
            std::cout << std::endl;*/

            int index = i;
            int runTime = 0;

            if(time < set[i+1].arrival && set[i+1].arrival < time + set[i].burstTime && set[i+1].priority < set[i].priority){
                runTime = set[i+1].arrival - time;
                i--;
            } else{
                runTime = set[i].burstTime;
                for(int j = i; j < size; j++){
                    if(set[j].arrival < time + set[i].burstTime && set[j].priority < set[i].priority){
                        runTime = set[j].arrival - time;
                        i--;
                        break;
                    }
                }
            }

            set[index].burstTime -= runTime;
            set[index].arrival += runTime;

            for(int k = i; k < size; k++){
                if(set[k].arrival < time + runTime && k != i){
                    set[k].arrival = time + runTime;
                }
            }

            if(set[index].burstTime > 0){
                std::cout << time << " " << set[index].index << " " << runTime << std::endl;
            } else{
                std::cout << time << " " << set[index].index << " " << runTime << "X" << std::endl;
            }

            time += runTime;
        }
    }
}

#endif