#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Process
{
    string name;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int responseTime;
    int startTime;
    int completionTime;
    int turnAroundTime; // completion time - arrival time
};

bool compareArrival(Process a, Process b)
{
    return a.arrivalTime < b.arrivalTime;
}

void firstComeFirstServed(vector<Process> &processes)
{
    sort(processes.begin(), processes.end(), compareArrival);

    int currentTime = 0;
    float totalWaitingTime = 0, totalResponseTime = 0, totalTurnAroundTime = 0;

    for (int i = 0; i < processes.size(); i++)
    {
        if (currentTime < processes[i].arrivalTime)
        {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].startTime = currentTime;
        processes[i].responseTime = currentTime - processes[i].arrivalTime;
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;

        processes[i].completionTime = processes[i].startTime + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;

        currentTime += processes[i].burstTime;
        totalWaitingTime += processes[i].waitingTime;
        totalResponseTime += processes[i].responseTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
    }

    cout << "\n------ FIFO Scheduling ------\n";
    cout << "Process\t\tArrival\t\tBurst\t\tWaiting\t\tResponse\tTurnaround" << endl;

    for (const auto &p : processes)
    {
        cout << p.name << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.waitingTime << "\t\t" << p.responseTime << "\t\t" << p.turnAroundTime << "\n";
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

    firstComeFirstServed(processes);

    return 0;
}