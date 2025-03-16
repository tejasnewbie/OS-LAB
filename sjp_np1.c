#include <stdio.h>

typedef struct {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void sortByBurstTime(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].burst_time > p[j + 1].burst_time) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(Process p[], int n) {
    p[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
    }
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

void printProcesses(Process p[], int n) {
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }
}

int main() {
    Process processes1[] = {{1, 6}, {2, 8}, {3, 7}, {4, 3}};
    int n1 = sizeof(processes1) / sizeof(processes1[0]);

    printf("Test Case 1:\n");
    sortByBurstTime(processes1, n1);
    calculateTimes(processes1, n1);
    printProcesses(processes1, n1);

    Process processes2[] = {{1, 2}, {2, 4}, {3, 1}, {4, 3}};
    int n2 = sizeof(processes2) / sizeof(processes2[0]);

    printf("\nTest Case 2:\n");
    sortByBurstTime(processes2, n2);
    calculateTimes(processes2, n2);
    printProcesses(processes2, n2);

    return 0;
}
