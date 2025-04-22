#include <iostream>
#include <vector>

using namespace std;

struct Process
{
    string name;
    int arrivalTime;
    int burstTime;
    int startTime;
    int waitingTime;
    int responseTime;
    int turnAroundTime;
    bool isCompleted = false;
};

void shortestJobFirst(vector<Process>& processes)
{
    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0, totalResponseTime = 0, totalTurnAroundTime = 0;

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
            Process &p = processes[index];
            p.startTime = currentTime;
            p.responseTime = p.startTime - p.arrivalTime;
            p.waitingTime = p.startTime - p.arrivalTime;

            int completionTime = p.startTime + p.burstTime;
            p.turnAroundTime = completionTime - p.arrivalTime;

            currentTime += p.burstTime;
            p.isCompleted = true;
            completed++;
            
            totalWaitingTime += p.waitingTime;
            totalResponseTime += p.responseTime;
            totalTurnAroundTime += p.turnAroundTime;
        }
        else
            currentTime++; // CPU idle
    }

    cout << "\n------ SJF (Non-Preemptive) Scheduling ------\n";
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

    shortestJobFirst(processes);

    return 0;
}