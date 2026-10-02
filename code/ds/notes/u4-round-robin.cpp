#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Process { int id, burstTime, arrivalTime, remaining, completion; };

int main() {                                  // Practice sheet 3, Q10
    Process p[] = {{1, 5, 0, 5, 0}, {2, 3, 1, 3, 0}, {3, 1, 2, 1, 0}, {4, 4, 3, 4, 0}};
    const int n = 4, quantum = 2;

    // #region rr
    queue<int> rq;                            // indices into p[]
    int time = 0, arrived = 0;
    while (arrived < n && p[arrived].arrivalTime <= time) rq.push(arrived++);
    cout << "Gantt chart:" << endl;
    while (!rq.empty()) {
        int i = rq.front(); rq.pop();
        int run = min(quantum, p[i].remaining);   // the last slice may be shorter
        cout << "  " << time << "-" << time + run << " P" << p[i].id << endl;
        time += run;
        p[i].remaining -= run;
        while (arrived < n && p[arrived].arrivalTime <= time) rq.push(arrived++);   // arrivals first
        if (p[i].remaining > 0) rq.push(i);       // then the preempted process
        else p[i].completion = time;
    }
    // #endregion rr

    double tat = 0, wt = 0;
    for (int i = 0; i < n; i++) {
        int t = p[i].completion - p[i].arrivalTime;   // turnaround = completion - arrival
        int w = t - p[i].burstTime;                   // waiting = turnaround - burst
        cout << "P" << p[i].id << ": completion " << p[i].completion
             << ", turnaround " << t << ", waiting " << w << endl;
        tat += t; wt += w;
    }
    cout << "average turnaround " << tat / n << ", average waiting " << wt / n << endl;
    return 0;
}
