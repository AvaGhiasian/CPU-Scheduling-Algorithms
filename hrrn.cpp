#include <iostream>
#include <vector>
#include <string>

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
    bool isCompleted = false;
};

void highestResponseRatioNext(vector<Process> &processes)
{
    int currentTime = 0, completed = 0;
    float totalWaitingTime = 0, totalResponseTime = 0, totalTurnAroundTime = 0;

    while (completed < processes.size())
    {
        int index = -1;
        float highestRatio = -1.0;

        for (int i = 0; i < processes.size(); i++)
        {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime)
            {
                int waitingTime = currentTime - processes[i].arrivalTime;
                float responseRatio = (float)(waitingTime + processes[i].burstTime) / processes[i].burstTime;

                if (responseRatio > highestRatio)
                {
                    highestRatio = responseRatio;
                    index = i;
                }
            }
        }

        if (index == -1)
        {
            currentTime++; // cpu is idle
        }
        else
        {
            Process &p = processes[index];
            p.startTime = currentTime;
            p.responseTime = p.startTime - p.arrivalTime;
            p.waitingTime = p.startTime - p.arrivalTime;

            p.completionTime = currentTime + p.burstTime;
            p.turnAroundTime = p.completionTime - p.arrivalTime;

            currentTime += p.burstTime;
            p.isCompleted = true;
            completed++;

            totalWaitingTime += p.waitingTime;
            totalResponseTime += p.responseTime;
            totalTurnAroundTime += p.turnAroundTime;
        }
    }

    cout << "\n------ Highest Response Ratio Next (HRRN) Scheduling ------\n";
    cout << "Process\t\tArrival\t\tBurst\t\tWaiting\t\tResponse\tTurnaround\n";
    for (const auto &p : processes)
    {
        cout << p.name << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t"
             << p.waitingTime << "\t\t" << p.responseTime << "\t\t" << p.turnAroundTime << "\n";
    }

    cout << "\nAverage Waiting Time: " << totalWaitingTime / processes.size() << "\n";
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

    highestResponseRatioNext(processes);

    return 0;
}