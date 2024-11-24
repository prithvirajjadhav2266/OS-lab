#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

struct Process
{
    string processId;
    int at;
    int bt;
    int ct = -1;
    int tat = -1;
    int wt = -1;
};

int main()
{
    int n;

    // Input the number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    // Input validation
    if (n <= 0)
    {
        cerr << "Invalid number of processes." << endl;
        return 1;
    }

    vector<Process> processes(n);

    // Input the process details
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "Enter Process Id, Arrival time and Burst time and priority respectively: ";
        cin >> processes[i].processId >> processes[i].at >> processes[i].bt;
        cout << endl;
    }

    // Sort processes based on Arrival Time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.at < b.at; });

    // Display sorted processes
    cout << "User input after sorting:" << endl;
    cout << "Process    AT      BT" << endl;
    for (const auto &process : processes)
    {
        cout << process.processId << "        " << process.at << "        " << process.bt << endl;
    }

    // Calculate Completion Time (CT), Turn Around Time (TAT), and Waiting Time (WT)
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        if (currentTime < processes[i].at)
        {
            currentTime = processes[i].at; // Processor is idle until the next process arrives
        }

        currentTime += processes[i].bt;
        processes[i].ct = currentTime;
    }

    // Calculating Turn around time

    for (int i = 0; i < n; i++)
    {
        processes[i].tat = processes[i].ct - processes[i].at;
    }

    // Calculating Waiting Time

    for (int i = 0; i < n; i++)
    {
        processes[i].wt = processes[i].tat - processes[i].bt;
    }

    // Display process times
    cout << "Process ID\tArrival Time\tBurst Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].processId << "\t\t" << processes[i].at << "\t\t" << processes[i].bt << endl;
    }
    cout << endl;
    cout << "Completion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].ct << "\t\t" << processes[i].tat << "\t\t" << processes[i].wt << endl;
    }

    // print average for waiting time and completion time

    double ct_avg = 0;
    double avg = 0;

    for (int i = 0; i < n; i++)
    {
        avg += processes[i].wt;
    }

    avg /= n;

    for (int i = 0; i < n; i++)
    {
        ct_avg += processes[i].ct;
    }

    ct_avg /= n;

    cout << endl;
    cout << "The average of completion time: " << ct_avg << endl;
    cout << "The average of waiting time: " << avg;

    return 0;
}