#include "SJF.h"

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
            
            queue.push(process);
            set.push_back(process);
        }

        int time = 0;
        while(!queue.empty()){
            Process p = queue.top();
            //cout << time << " " << p.index << " " << p.burstTime << "X" << endl;

            time += p.burstTime;

            queue.pop();
        }

        srtf(set);
    }

    return 0;
}