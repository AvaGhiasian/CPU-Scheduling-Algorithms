#include <iostream>
#include <vector>
#include <string>

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

void roundRobin(vector<Process> &processes, int quantum)
{
    int currentTime = 0, completed = 0;
    int remainingProcesses = processes.size();

    float totalWaitingTime = 0, totalResponseTime = 0;

    for (int i = 0; i < processes.size(); i = (i + 1) % processes.size()) // circular loop
    {
        if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime)
        {
            if (processes[i].remainingTime == processes[i].burstTime)
            {
                processes[i].responseTime = currentTime;
            }

            if (processes[i].remainingTime <= quantum)
            {
                currentTime += processes[i].remainingTime;
                processes[i].completionTime = currentTime;
                processes[i].remainingTime = 0;
                remainingProcesses--;
            }
            else
            {
                currentTime += quantum;
                processes[i].remainingTime -= quantum;
            }
        }

        if (remainingProcesses == 0)
        {
            break;
        }
    }

    for (auto &p : processes)
    {
        p.waitingTime = p.completionTime - p.arrivalTime - p.burstTime;
        p.responseTime = p.completionTime - p.arrivalTime;

        totalResponseTime += p.responseTime;
        totalWaitingTime += p.waitingTime;
    }

    cout << "\n------ Round Robin Scheduling ------\n";
    cout << "Process\t\tArrival\t\tBurst\t\tWaiting\t\tResponse\t\n";
    for (const auto &p : processes)
    {
        cout << p.name << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.waitingTime << "\t\t" << p.responseTime << "\t\t\n";
    }

    cout << "Average Waiting Time: " << totalWaitingTime / processes.size() << "\n";
    cout << "Average Response Time: " << totalResponseTime / processes.size() << "\n";
}

int main()
{
    int n, quantum;
    vector<Process> processes;

    cout << "Enter quantum time (ms): ";
    cin >> quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    // vector<Process> processes = {
    //     {"P1", 0, 8, 0, 0},
    //     {"P2", 0, 4, 0, 0},
    //     {"P3", 0, 9, 0, 0},
    //     {"P4", 0, 5, 0, 0}};

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

    roundRobin(processes, quantum);

    return 0;
}