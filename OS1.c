#include <stdio.h>

void findCompletionTime(int processes[], int n, int bt[], int at[], int ct[]) {
    ct[0] = at[0] + bt[0]; 
    for (int i = 1; i < n; i++) {
        ct[i] = (ct[i - 1] > at[i] ? ct[i - 1] : at[i]) + bt[i];
    }
}

void findTurnaroundTime(int processes[], int n, int bt[], int at[], int ct[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];  
    }
}

void findWaitingTime(int processes[], int n, int bt[], int at[], int tat[], int wt[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];  
    }
}

void findAvgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], ct[n];
    findCompletionTime(processes, n, bt, at, ct);
    findTurnaroundTime(processes, n, bt, at, ct, tat);
    findWaitingTime(processes, n, bt, at, tat, wt);

    int total_wt = 0, total_tat = 0;

    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], at[i], wt[i], tat[i], ct[i]);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", (float)total_tat / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], bt[n], at[n];

    printf("Enter the burst times and arrival times of the processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time of process %d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Arrival time of process %d: ", i + 1);
        scanf("%d", &at[i]);
        processes[i] = i + 1;  // Process IDs start from 1
    }

    findAvgTime(processes, n, bt, at);

    return 0;
}