#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

void calculateTimes(Process p[], int n) {
    int complete = 0, time = 0, shortest = -1;
    int min_time = INT_MAX, finish_time;
    int is_completed[n];

    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
        p[i].remaining_time = p[i].burst_time;
    }

    while (complete < n) {
        min_time = INT_MAX;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !is_completed[i] && p[i].remaining_time < min_time) {
                min_time = p[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        p[shortest].remaining_time--;

        if (p[shortest].remaining_time == 0) {
            complete++;
            finish_time = time + 1;
            p[shortest].completion_time = finish_time;
            p[shortest].turnaround_time = finish_time - p[shortest].arrival_time;
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;
            is_completed[shortest] = 1;
        }

        time++;
    }
}

void printProcesses(Process p[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }
}

int main() {
    Process processes1[] = {{1, 0, 6}, {2, 2, 8}, {3, 4, 7}, {4, 5, 3}};
    int n1 = sizeof(processes1) / sizeof(processes1[0]);

    printf("Test Case 1:\n");
    calculateTimes(processes1, n1);
    printProcesses(processes1, n1);

    Process processes2[] = {{1, 0, 3}, {2, 1, 1}, {3, 2, 6}, {4, 3, 2}};
    int n2 = sizeof(processes2) / sizeof(processes2[0]);

    printf("\nTest Case 2:\n");
    calculateTimes(processes2, n2);
    printProcesses(processes2, n2);

    return 0;
}
