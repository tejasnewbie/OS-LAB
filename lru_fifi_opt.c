#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void fifo(int pages[], int n, int capacity) {
    int frame[capacity], index = 0, pageFaults = 0;
    for (int i = 0; i < capacity; i++) frame[i] = -1;
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[index] = pages[i];
            index = (index + 1) % capacity;
            pageFaults++;
        }
    }
    printf("\nFIFO Page Replacement:\nPage Faults: %d\n", pageFaults);
}

void lru(int pages[], int n, int capacity) {
    int frame[capacity], lastUsed[MAX], pageFaults = 0;
    for (int i = 0; i < capacity; i++) frame[i] = -1;
    for (int i = 0; i < n; i++) {
        int found = 0, leastRecent = -1, leastTime = MAX;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                lastUsed[j] = i;
                break;
            }
            if (frame[j] != -1 && lastUsed[j] < leastTime) {
                leastTime = lastUsed[j];
                leastRecent = j;
            }
        }
        if (!found) {
            if (leastRecent != -1) {
                frame[leastRecent] = pages[i];
                lastUsed[leastRecent] = i;
            }
            pageFaults++;
        }
    }
    printf("\nLRU Page Replacement:\nPage Faults: %d\n", pageFaults);
}

void optimal(int pages[], int n, int capacity) {
    int frame[capacity], pageFaults = 0;
    for (int i = 0; i < capacity; i++) frame[i] = -1;
    for (int i = 0; i < n; i++) {
        int found = 0, farthest = -1, replaceIndex = -1;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    replaceIndex = j;
                    break;
                }
            }
            frame[replaceIndex] = pages[i];
            pageFaults++;
        }
    }
    printf("\nOptimal Page Replacement:\nPage Faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX], n, capacity;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter pages:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter capacity of page frames: ");
    scanf("%d", &capacity);
   
    fifo(pages, n, capacity);
    lru(pages, n, capacity);
    optimal(pages, n, capacity);
   
    return 0;
}
