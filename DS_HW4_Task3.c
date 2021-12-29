#include<stdio.h>

int isConnected(int aMatrix[128][128], int size);
void showAdjacencyMatrix(int aMatrix[][128], int size);
int isAllAppended(int status[128], int size);
int findMinWeight(int edges[128], int status[128], int size);
int getWeight(int aList[128][3], int line, int size);

int main(void) {
    int size, line, aList[128][3] = {0}, aMatrix[128][128] = {0}, weight;

    scanf("%d %d", &size, &line);
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &aList[i][j]);
        }
        aMatrix[aList[i][0]][aList[i][1]] = aList[i][2];
        aMatrix[aList[i][1]][aList[i][0]] = aList[i][2];
    }

    if (isConnected(aMatrix, size)) {
        weight = getWeight(aList, line, size);
        printf("> %d\n", weight);
    } else {
        printf("> NO connected\n");
    }
    showAdjacencyMatrix(aMatrix, size);

    return 0;
}

int isConnected(int aMatrix[128][128], int size) {
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

void showAdjacencyMatrix(int aMatrix[][128], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", aMatrix[i][0]);
        for (int j = 1; j < size; j++) {
            printf(" %d", aMatrix[i][j]);
        }
        printf("\n");
    }
}

int isAllAppended(int status[128], int size) {
    for (int i = 0; i < size; i++) {
        if (status[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int findMinWeight(int edges[128], int status[128], int size) {
    int min[2] = {-1, 10001}, flag = 0;

    for (int i = 0; i < size; i++) {
        if (edges[i] != 0 && status[i] == 0) {
            if (edges[i] < min[1]) {
                min[0] = i;
                min[1] = edges[i];
                flag = 1;
            }
            if (edges[i] == min[1]) {
                if (i < min[0]) {
                    min[0] = i;
                    min[1] = edges[i];
                    flag = 1;
                }
            }
        }
    }

    return flag ? min[0] : -1;
}

int getWeight(int aList[128][3], int line, int size) {
    int min, status[128] = {0};

    while (isAllAppended(status, size)) {

    }

    return weight;
}

