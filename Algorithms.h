#ifndef _SJF_h
#define _SJF_h

using namespace std;

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

//-------------------------
// Helper Methods
//-------------------------
bool compareArrivalTime(Process& p1, Process& p2){
    return p1.arrival < p2.arrival;
}

bool compareBurstTime(Process& p1, Process& p2){
    return p1.burstTime < p2.burstTime;
}

bool compareShortestRemaining(Process& p1, Process& p2){
    return (p1.arrival <= p2.arrival && p1.burstTime < p2.burstTime);
}

bool comparePriority(Process& p1, Process& p2){
    return (p1.arrival <= p2.arrival && p1.priority < p2.priority);
}

int searchCoverage(vector<Process>& set, int left, int right, int burstTime){
    int retVal = 0;
    //cout << "left:" << left << "  right:" << right << " burst:" << burstTime << endl;
    while(left <= right){
        int middle = (left + right) / 2;
        //cout << "mid:" << middle << endl;
        if(set[middle].arrival > burstTime){
            right = middle - 1;
        }
        else if(set[middle].arrival < burstTime || set[middle].arrival == burstTime){
            retVal = middle;
            left = middle + 1;
        }
    }
    return retVal;
}

void pushProcesses(deque<Process>& q, vector<Process>& set, int start, int next, int preempted){
    for(int i = start; i < next; i++){
        q.emplace(q.end() - preempted, set[i]);
    }
}

//-------------------------
// Scheduling Algorithms
//-------------------------
void fcfs(vector<Process>& set){
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

void sjf(vector<Process>& set){
    int size = set.size();
    int time = 0;
    int next =  0;

    sort(set.begin(), set.end(), compareArrivalTime);

    for(int i = 0; i < size; i++){
        if(set[i].arrival > time){
            time = set[i].arrival;
        }
        cout << time << " " << set[i].index << " " << set[i].burstTime << "X" << endl;
        time+= set[i].burstTime;

        if(set[next].arrival <= time){
            if(i < size - 1){
                int burstCoverage = searchCoverage(set, i + 1, size - 1, time);
                if(burstCoverage > 0){
                    sort(set.begin()+i+1, set.begin()+burstCoverage+1, compareBurstTime);
                    next = burstCoverage + 1;
                }
            }
        }
    }
}

void srtf(vector<Process>& set){
    int size = set.size();
    int time = 0;
    
    sort(set.begin(), set.end(), compareArrivalTime);
    sort(set.begin(), set.end(), compareShortestRemaining);

    for(int i = 0; i < size; i++){
        if(set[i].burstTime > 0){
            if(set[i].arrival > time){
                time = set[i].arrival;
            }

            sort(set.begin(), set.end(), compareShortestRemaining);

            int index = i;
            int runTime = 0;

            if(time < set[i+1].arrival && set[i+1].arrival < time + set[i].burstTime && set[i+1].burstTime < set[i].burstTime){
                runTime = set[i+1].arrival - time;
                i--;
            } else{
                runTime = set[i].burstTime;
                for(int j = i; j < size; j++){
                    if(set[j].arrival < time + set[i].burstTime && time + set[j].burstTime < (time + set[i].burstTime) - (set[j].arrival - time)){
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
                cout << time << " " << set[index].index << " " << runTime << endl;
            } else{
                cout << time << " " << set[index].index << " " << runTime << "X" << endl;
            }

            time += runTime;
        }
    }

}

void p(vector<Process>& set){
    int size = set.size();
    int time = 0;

    sort(set.begin(), set.end(), compareArrivalTime);
    sort(set.begin(), set.end(), comparePriority);

    for(int i = 0; i < size; i++){
        if(set[i].burstTime > 0){
            if(set[i].arrival > time){
                time = set[i].arrival;
            }

            sort(set.begin(), set.end(), comparePriority);

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
                cout << time << " " << set[index].index << " " << runTime << endl;
            } else{
                cout << time << " " << set[index].index << " " << runTime << "X" << endl;
            }

            time += runTime;
        }
    }
}

void rr(vector<Process>& set, int quantum){
    int size = set.size();
    int time = 0;
    int processed = 0;
    int start = 0;
    int next = 1;
    int modifier = 0;
    int preempted = 0;

    sort(set.begin(), set.end(), compareArrivalTime);
    
    deque<Process> q;
    pushProcesses(q, set, start, next, preempted);

    while(processed < size){
        int nextArrival = set[next].arrival;
        
        bool requeue = false;
        while(time < nextArrival && processed < size){
            Process process = q.front();
            q.pop_front();

            if(process.arrival > time){
                time = process.arrival;
            }

            if(process.burstTime <= quantum){
                cout << time - (quantum * modifier) << " " << process.index << " " << process.burstTime + (quantum * modifier) << "X" << endl;
                time += process.burstTime;
                modifier = 0;
                if(q.size() + 1 <= preempted){
                    preempted--;
                }
                processed++;
            }
            else{
                if(time + quantum >= nextArrival || q.size() > 0){
                    cout << time - (quantum * modifier) << " " << process.index << " " << quantum + (quantum * modifier) << endl;
                    modifier = 0;
                }
                else{
                    modifier++;
                }
                time += quantum;

                process.burstTime -= quantum;
                requeue = true;
            }

            if(time >= nextArrival) {
                start = next;
                next = searchCoverage(set, next, size - 1, time) + 1;
                pushProcesses(q, set, start, next, preempted);
            }
            if(requeue){
                q.push_back(process);
                preempted++;
                requeue = false;
            }
        }
    }
}

#endif