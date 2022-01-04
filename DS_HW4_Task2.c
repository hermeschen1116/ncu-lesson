#include<stdio.h>

int isConnected(int a_matrix[32][32], int size);
int isAllAppended(int status[32], int size);
int findMinWeight(int edges[32], int status[32], int size);
int compareMinWeight(int a_matrix[32][32], int status[32], int size, int end_index, int start_index);
int findParent(int path[32][32], int size, int *cnt, int end);
int getWeight(int a_matrix[32][32], int size);
void showStatus(int status[32], int size) {
    printf("%d", status[0]);
    for (int i = 1; i < size; i++) {
        printf(" %d", status[i]);
    }
}

int main(void) {
    int size, aMatrix[32][32] = {0}, weight;

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

int isConnected(int a_matrix[32][32], int size) {
    int nonZero_cnt, pair_cnt = 0;

    for (int i = 1; i < size; i++) {
        nonZero_cnt = 0;
        for (int j = 0; j < i; j++) {
            if (a_matrix[i][j] != 0) {
                nonZero_cnt++;
            }
        }
        if (nonZero_cnt > 0) {
            pair_cnt++;
        }
    }
    if (pair_cnt == size-1) {
        return 1;
    }
    return 0;
}

int isAllAppended(int status[32], int size) {
    for (int i = 0; i < size; i++) {
        if (status[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int findMinWeight(int edges[32], int status[32], int size) {
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

int compareMinWeight(int a_matrix[32][32], int status[32], int size, int end_index, int start_index) {
    int end_min = findMinWeight(a_matrix[end_index], status, size);
    int start_min = findMinWeight(a_matrix[start_index], status, size);

    return end_min != -1 && start_min != -1 && a_matrix[end_index][end_min] < a_matrix[start_index][start_min] ? 1 : 0;
}

int findParent(int path[32][32], int size, int *cnt, int end) {
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

int getWeight(int a_matrix[32][32], int size) {
    int status[32] = {0}, path[32][32] = {0}, start_cnt = 0, end_cnt = 0;
    int start = 0, end = 0, weight = 0, next_vertex, flag = 1;

    status[0] = 1;
    while (isAllAppended(status, size) == 0) {
        if (flag) {
            next_vertex = findMinWeight(a_matrix[end], status, size);
            if (next_vertex != -1) {
                if (end_cnt != 0 && compareMinWeight(a_matrix, status, size, end, start) == 0) {
                    flag = 0;
                    continue;
                }
                weight += a_matrix[end][next_vertex];
                path[end][next_vertex] = end_cnt*2+1;
                ++end_cnt;
                end = next_vertex;
            } else {
                end = findParent(path, size, &end_cnt, 1);
                flag = 0;
            }
        } else {
            next_vertex = findMinWeight(a_matrix[start], status, size);
            if (next_vertex != -1) {
                if (start_cnt != 0 && compareMinWeight(a_matrix, status, size, end, start) == 1) {
                    flag = 1;
                    continue;
                }
                weight += a_matrix[start][next_vertex];
                path[start][next_vertex] = start_cnt*2;
                ++start_cnt;
                start = next_vertex;
            } else {
                start = findParent(path, size, &start_cnt, 0);
                flag = 1;
            }
        }
        status[next_vertex] = 1;
    }

    return weight;
}


