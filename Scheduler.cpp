#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <algorithm>

#include "Algorithms.h"

using namespace std;

int main(){
    
    int testCases;
    cin >> testCases;

    for(int i= 0; i < testCases; i++){
        int processCount, interval;
        string algorithm;

        cin >> processCount >> algorithm;
        vector<Process> set;

        if(algorithm == "RR"){
            cin >> interval;
        }

        //Sort processes by arriaval time
        for(int j = 0; j < processCount; j++){
            int arrival, burstTime, priority;
            cin >> arrival >> burstTime >> priority;

            Process process(j + 1, arrival, burstTime, priority);
            
            set.push_back(process);
        }

        if(algorithm == "FCFS"){
            fcfs(set);
        } else if(algorithm == "SJF"){
            sjf(set);
        } else if(algorithm == "SRTF"){
            srtf(set);
        } else if(algorithm == "P"){
            p(set);
        } else if(algorithm == "RR"){
            //rr(set);
        }
    }

    return 0;
}