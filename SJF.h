#ifndef _SJF_h
#define _SJF_h

#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <algorithm>

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

struct SJFComparator{
    int currentTime;
    int index;

    bool operator()(const Process &p1, const Process &p2)
    { 
        if(p1.arrival >= currentTime){
            currentTime = p1.burstTime;
            index = p1.index;
            return true;
        }
        return (p1.burstTime > p2.burstTime) || p2.index == index;
    }
};

bool compareArrivalTime(Process p1, Process p2){
    return (p1.arrival < p2.arrival);
}

<<<<<<< HEAD
bool compareShortestRemaining(Process p1, Process p2){
    /*if(p1.arrival < p2.arrival){
        return (p1.arrival + p1.burstTime < p1.arrival + p2.arrival + p2.burstTime);
    } else if(p1.arrival == p2.arrival){
        return (p1.burstTime < p2.burstTime);
    } else{
        return (p2.arrival + p1.burstTime < p2.arrival + p1.arrival + p2.burstTime);
    }*/

    return (p1.arrival <= p2.arrival && p1.burstTime < p2.burstTime);
}

void fcfs(std::vector<Process> set){
    //int size = sizeof(set)/sizeof(set[0]);
    int size = set.size();
    int time = 0;

    sort(set.begin(), set.end(), compareArrivalTime);

    for(int i = 0; i < size; i++){
        if(set[i].arrival >= time){
            time = set[i].arrival;
        }

        std::cout << time << " " << set[i].index << " " << set[i].burstTime << std::endl;
        time += set[i].burstTime;
    }
}

void srtf(vector<Process> set){
    int size = set.size();
    int time = 0;
    
    std::sort(set.begin(), set.end(), compareArrivalTime);
    std::sort(set.begin(), set.end(), compareShortestRemaining);

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

#endif