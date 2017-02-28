#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <queue>
#include <vector>

#include "SJF.h"

using namespace std;

int main(){
    
    int testCases;
    cin >> testCases;

    for(int i= 0; i < testCases; i++){
        int processCount;
        string algorithm;

        cin >> processCount >> algorithm;

        priority_queue<Process, vector<Process>, SJFComparator> queue;

        for(int j = 1; j <= processCount; j++){
            int arrival, burstTime, priority;
            cin >> arrival >> burstTime >> priority;

            Process process(j, arrival, burstTime, priority);

            queue.push(process);
        }

        int time = 0;
        while(!queue.empty()){
            Process p = queue.top();
            cout << time << " " << p.index << " " << p.burstTime << "X" << endl;

            time += p.burstTime;

            queue.pop();
        }
    }

    return 0;
}