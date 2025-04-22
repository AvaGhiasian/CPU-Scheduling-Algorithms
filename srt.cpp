#include <iostream>
#include <vector>
#include <string>

using namespace std;

// response, waiting, turnaround works wrong

struct Process
{
    string name;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int responseTime;
    int turnAroundTime; // completion time - arrival time
    int startTime = -1;
    bool isCompleted = false;
};


void shortestRemainingTime(vector<Process> &processes)
{
    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0, totalResponseTime = 0, totalTurnAroundTime = 0;

    for (int i = 0; i < processes.size(); i++)
    {
        processes[i].remainingTime = processes[i].burstTime;
    }

    while (completed < processes.size())
    {
        int index = -1;
        int minRemaining = INT_MAX;

        // finds smallest cbt each time
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
            Process &p = processes[index];
            if (p.startTime == -1)
                p.startTime = currentTime;

            p.remainingTime--;
            currentTime++;

            if (p.remainingTime == 0)
            {
                p.completionTime = currentTime;
                p.turnAroundTime = p.completionTime - p.arrivalTime;
                p.waitingTime = p.turnAroundTime - p.burstTime;
                p.responseTime = p.startTime - p.arrivalTime;
                p.isCompleted = true;
                completed++;

                totalWaitingTime += p.waitingTime;
                totalResponseTime += p.responseTime;
                totalTurnAroundTime += p.turnAroundTime;
            }
        }
        else
        {
            currentTime++;  // cpu is idle 
        }
    }

    cout << "\n------ SRT (Preemptive SJF) Scheduling ------\n";
    cout << "Process\t\tArrival\t\tBurst\t\tWaiting\t\tResponse\tTurnaround\n";
    for (const auto &p : processes)
    {
        cout << p.name << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.waitingTime << 
        "\t\t" << p.responseTime << "\t\t" << p.turnAroundTime << "\n";
    }

    cout << "Average Waiting Time: " << totalWaitingTime / processes.size() << "\n";
    cout << "Average Response Time: " << totalResponseTime / processes.size() << "\n";
    cout << "Average Turn Around Time: " << totalTurnAroundTime / processes.size() << "\n";
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
        processes.push_back(p);
    }

    shortestRemainingTime(processes);

    return 0;
}