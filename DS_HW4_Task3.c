#include<stdio.h>
#include<stdlib.h>

int restoreMatrix
int isConnected(int aMatrix[32][32], int size);

int main(void) {
    int m, n, aMatrix[32][32] = {0}, weight = 0;

    scanf("%d %d", &m, &n);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &aMatrix[i][j]);
        }
    }

    if (isConnected(aMatrix, size)) {
        printf("> %d\n", weight);
    } else {
        printf("> NO connected\n");
    }

    return 0;
}

int isConnected(int aMatrix[32][32], int size) {
    int nonZeroCnt, pairCnt = 0;

    for (int i = 1; i < size; i++) {
        nonZeroCnt = 0;
        for (int j = 0; j < i; j++) {
            if (aMatrix[i][j] != 0) {
                nonZeroCnt++;
            }
        }
        if (nonZeroCnt > 0) {
            pairCnt++;
        }
    }
    if (pairCnt == size-1) {
        return 1;
    }
    return 0;
}
