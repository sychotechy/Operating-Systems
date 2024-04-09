#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time
};

// Function to find the process with the shortest remaining burst time
int findShortestJob(struct Process processes[], int n, int current_time,int rt[]) {
    int shortest_job = -1;
    int min_burst_time = INT_MAX;

    for (int i = 0; i <n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].burst_time <= min_burst_time && rt[i]!=0) {
            min_burst_time = processes[i].burst_time;
            shortest_job = i;
        }
    }

    return shortest_job;
}

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process processes[], int n, int wt[], int tat[]) {
    int remaining_time[n];
    for (int i = 0; i < n; i++)
        remaining_time[i] = processes[i].burst_time;

    int completed = 0;
    int current_time = 0;
  int shortest_jobs[50];
  int i=0;
    while (completed < n) {
        int shortest_job = findShortestJob(processes, n, current_time,remaining_time);
        printf("Executing P%d\n",shortest_job); 
        shortest_jobs[i++]=shortest_job;
        if (shortest_job == -1) {
            current_time++;
            continue;
        }

        //if (remaining_time[shortest_job] == processes[shortest_job].burst_time)
        //    {wt[shortest_job] = current_time - processes[shortest_job].arrival_time;}

        remaining_time[shortest_job]--;
        current_time++;

        if (remaining_time[shortest_job] == 0) {
            tat[shortest_job] = current_time - processes[shortest_job].arrival_time;
            wt[shortest_job]=tat[shortest_job]-processes[shortest_job].burst_time;
            completed++;
        }
      
    }
}

// Function to calculate average waiting time and turnaround time
void calculateAvgTimes(struct Process processes[], int n) {
    int wt[n], tat[n];
    calculateTimes(processes, n, wt, tat);
    printf("WT \t TAT\n");
   for(int i=0;i<n;i++)
     printf("%d\t %d\n",wt[i],tat[i]);
    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("Average waiting time = %.2f\n", avg_wt / n);
    printf("Average turnaround time = %.2f\n", avg_tat / n);
}

int main() {
    int n = 5; // Number of processes
    struct Process processes[] = {
        {1, 0, 8},
        {2, 1, 1},
        {3, 2, 3},
        {4, 3, 2},
        {5, 4, 6}
    };

    // Calculate average waiting time and turnaround time
    calculateAvgTimes(processes, n);

    return 0;
}
