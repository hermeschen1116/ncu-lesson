#include<stdio.h>

int isConnected(int aMatrix[256][256], int size);
int isAllAppended(int status[256], int size);
int findMinWeight(int edges[256], int status[256], int size);
int compareMinWeight(int aMatrix[256][256], int status[256], int size, int eIndex, int sIndex);
int findParent(int path[256][256], int size, int *cnt, int end);
int getWeight(int aMatrix[256][256], int size);

int main(void) {
    int size, aMatrix[256][256] = {0}, weight;

    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &aMatrix[i][j]);
        }
    }

    if (isConnected(aMatrix, size)) {
        weight = getWeight(aMatrix, size);
        printf("> %d\n", weight);
    } else {
        printf("> NO connected\n");
    }

    return 0;
}

int isConnected(int aMatrix[256][256], int size) {
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

int isAllAppended(int status[256], int size) {
    for (int i = 0; i < size; i++) {
        if (status[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int findMinWeight(int edges[256], int status[256], int size) {
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

int compareMinWeight(int aMatrix[256][256], int status[256], int size, int eIndex, int sIndex) {
    int eMin = findMinWeight(aMatrix[eIndex], status, size);
    int sMin = findMinWeight(aMatrix[sIndex], status, size);

    return eMin != -1 && sMin != -1 && aMatrix[eIndex][eMin] < aMatrix[sIndex][sMin] ? 1 : 0;
}

int findParent(int path[256][256], int size, int *cnt, int end) {
    int parent;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (path[i][j] == *cnt*2+end) {
                path[i][j] = 0;
            }
            if (path[i][j] == (*cnt-1)*2+end) {
                *cnt -= 1;
                parent = i;
                break;
            }
        }
    }

    return parent;
}

int getWeight(int aMatrix[256][256], int size) {
    int status[256] = {0}, path[256][256] = {0}, sCnt = 0, eCnt = 0;
    int start = 0, end = 0, weight = 0, nextVertex, flag = 1;

    status[0] = 1;
    while (isAllAppended(status, size) == 0) {
        //printf("s: %d, e: %d --> %d\n", start, end, weight);
        if (flag) {
            nextVertex = findMinWeight(aMatrix[end], status, size);
            if (nextVertex != -1) {
                if (eCnt != 0 && compareMinWeight(aMatrix, status, size, end, start) == 0) {
                    flag = 0;
                    continue;
                }
                weight += aMatrix[end][nextVertex];
                path[end][nextVertex] = eCnt*2+1;
                ++eCnt;
                end = nextVertex;
            } else {
                end = findParent(path, size, &eCnt, 1);
                flag = 0;
            }
        } else {
            nextVertex = findMinWeight(aMatrix[start], status, size);
            if (nextVertex != -1) {
                if (sCnt != 0 && compareMinWeight(aMatrix, status, size, end, start) == 1) {
                    flag = 1;
                    continue;
                }
                weight += aMatrix[start][nextVertex];
                path[start][nextVertex] = sCnt*2;
                ++sCnt;
                start = nextVertex;
            } else {
                start = findParent(path, size, &sCnt, 0);
                flag = 1;
            }
        }
        status[nextVertex] = 1;
    }

    return weight;
}

