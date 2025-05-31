#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Process
{
    string name;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int completionTime;
    int responseTime;
    bool isCompleted = false;
};

vector<Process> sortByArrival(vector<Process> &processes)
{
    for (int i = 0; i < processes.size(); i++)
    {
        for (int j = i + 1; j < processes.size(); j++)
        {
            if (processes[j].arrivalTime < processes[i].arrivalTime)
            {
                Process temp = processes[j];
                processes[j] = processes[i];
                processes[i] = temp;
            }
        }
    }

    return processes;
}

void shortestJobFirst(vector<Process> &processes)
{
    processes = sortByArrival(processes);

    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0, totalResponseTime = 0;

    while (completed < processes.size())
    {
        int minBurst = INT_MAX;
        int index = -1;

        // finding the shortest process, and saving its index for processing
        for (int i = 0; i < processes.size(); i++)
        {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime)
            {
                if (processes[i].burstTime < minBurst)
                {
                    minBurst = processes[i].burstTime;
                    index = i;
                }
            }
        }

        if (index != -1)
        {
            processes[index].completionTime = currentTime + processes[index].burstTime;
            processes[index].waitingTime = processes[index].completionTime - processes[index].arrivalTime - processes[index].burstTime;
            processes[index].responseTime = processes[index].completionTime - processes[index].arrivalTime;

            totalWaitingTime += processes[index].waitingTime;
            totalResponseTime += processes[index].responseTime;

            currentTime = processes[index].completionTime;
            processes[index].isCompleted = true;
            completed++;
        }
        else
            currentTime++; // CPU is idle
    }

    cout << "\n------ SJF (Non-Preemptive) Scheduling ------\n";
    cout << "Process\t\tArrival\t\tBurst\t\tWaiting\t\tResponse\n";
    for (const auto &p : processes)
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
        processes.push_back(p);
    }

    shortestJobFirst(processes);

    return 0;
}