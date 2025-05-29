#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

struct Process
{
    string name;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int responseTime;
    int startTime = -1;
    bool isCompleted = false;
};

void shortestRemainingTime(vector<Process> &processes)
{
    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0, totalResponseTime = 0;

    while (completed < processes.size())
    {
        int index = -1;
        int minRemaining = INT_MAX;

        // find the smallest cbt each time
        for (int i = 0; i < processes.size(); i++)
        {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime && processes[i].remainingTime < minRemaining)
            {
                minRemaining = processes[i].remainingTime;
                index = i;
            }
        }

        if (index != -1)
        {
            if (processes[index].startTime == -1)
            {
                processes[index].startTime = currentTime;
            }

            processes[index].remainingTime--;
            currentTime++;

            if (processes[index].remainingTime == 0)
            {
                processes[index].completionTime = currentTime;
                processes[index].waitingTime = processes[index].completionTime - processes[index].arrivalTime - processes[index].burstTime;
                processes[index].responseTime = processes[index].completionTime - processes[index].arrivalTime;

                totalWaitingTime += processes[index].waitingTime;
                totalResponseTime += processes[index].responseTime;

                processes[index].isCompleted = true;
                completed++;

            }
        }
        else
        {
            currentTime++; // cpu is idle
        }
    }

    cout << "\n------ SRT (Preemptive SJF) Scheduling ------\n";
    cout << "Process\t\tArrival\t\tBurst\t\tWaiting\t\tResponse\tTurnaround\n";
    for (auto &p : processes)
    {
        cout << p.name << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.waitingTime << "\t\t" << p.responseTime << "\t\t\n";
    }

    cout << "Average Waiting Time: " << totalWaitingTime / processes.size() << "\n";
    cout << "Average Response Time: " << totalResponseTime / processes.size() << "\n";
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    // vector<Process> processes = {
    //     {"P1", 0, 8, 0, 0},
    //     {"P2", 0, 4, 0, 0},
    //     {"P3", 0, 9, 0, 0},
    //     {"P4", 0, 5, 0, 0}};

    vector<Process> processes;

    for (int i = 0; i < n; ++i)
    {
        Process p;
        cout << "Enter name of process " << i + 1 << ": ";
        cin >> p.name;
        cout << "Enter arrival time of " << p.name << ": ";
        cin >> p.arrivalTime;
        cout << "Enter burst time of " << p.name << ": ";
        cin >> p.burstTime;
        p.remainingTime = p.burstTime;
        processes.push_back(p);
    }

    shortestRemainingTime(processes);

    return 0;
}