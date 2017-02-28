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
        int processCount, interval;
        string algorithm;

        cin >> processCount >> algorithm;

        if(algorithm == "RR"){
            cin >> interval;
        }

        //Process pArray[processCount];

        for(int j = 0; j < processCount; j++){
            int arrival, burstTime, priority;
            cin >> arrival >> burstTime >> priority;

            Process process(j + 1, arrival, burstTime, priority);

            //pArray[j] = process;
        }
    }

    return 0;
}