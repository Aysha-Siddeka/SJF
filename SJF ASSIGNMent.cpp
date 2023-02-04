#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#define File freopen("input.txt","r",stdin)
using namespace std;


class process{
public:
    string name;
    int arrival_time;
    int cpu_burst_time;
    int starting_time;
    int ending_time;

    process(string Name, int Arrival_Time, int CPU_Burst_Time)
    {
        name = Name;
        arrival_time = Arrival_Time;
        cpu_burst_time = CPU_Burst_Time;
        starting_time = -1;
        ending_time = -1;
    }
    int waiting_time()
    {
        return starting_time - arrival_time;
    }
    int turnaround_time()
    {
      int finish_time = ending_time;
        return finish_time - arrival_time;
    }
};

bool compareA(process x, process y)
{
    if (x.arrival_time < y.arrival_time){
        return true;
    }
    else return false;
}
bool compareB(process x, process y)
{
    if(x.cpu_burst_time<y.cpu_burst_time)
    {
        return true ;
    }
    else
        return false;
}

int main()
{
    freopen("input.txt","r",stdin);
    //File;

    string nm;
    int atime, btime;

    vector <process> Processes;
    vector <process> New;

    while(cin>>nm>>atime>>btime){
        process p = process(nm, atime, btime);
        Processes.push_back(p);
    }


    sort(Processes.begin(), Processes.end(), compareA);

    int scheduling_time = Processes[0].arrival_time;
    int sz = Processes.size();
    int sum_waiting_time = 0, sum_turnaround_time = 0;

    while(Processes.size()>0)
    {
    int j;

    for(j=0;j<Processes.size();j++)
    {
        if(Processes[j].arrival_time <= scheduling_time)
        {
            New.push_back(Processes[j]);
        }
    }
    sort(New.begin(),New.end(),compareB);


    New[0].ending_time = scheduling_time+ New[0].cpu_burst_time;
    New[0].starting_time = scheduling_time;

    scheduling_time = New[0].ending_time;

    sum_waiting_time = sum_waiting_time + New[0].waiting_time();

    sum_turnaround_time = sum_turnaround_time + New[0].turnaround_time();

    vector<process>:: iterator itz;
    for(itz = Processes.begin();itz!=Processes.end();itz++)
    {
        if(itz->name == New[0].name)
        {
            Processes.erase(itz);
            break;
        }
    }
    New.clear(); // removes
    }

    double average_waiting_time, average_turnaround_time;
    average_waiting_time = (sum_waiting_time*1.0)/sz;
    average_turnaround_time = (sum_turnaround_time*1.0)/sz;

    cout<<"Average Waiting Time: "<< average_waiting_time<<endl;
    cout<<"Average Turnaround Time: "<< average_turnaround_time<<endl;
    return 0;
}
