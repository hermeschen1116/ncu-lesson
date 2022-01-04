#include<stdio.h>

int isConnected(int a_matrix[32][32], int size);
int isAppend(int path[32][32], int size, int index);
int isAllAppended(int path[32][32], int size);
int findMinWeight(int a_matrix[32][32], int path[32][32], int size, int index);
int compareMinWeight(int a_matrix[32][32], int path[32][32], int size, int end_index, int start_index);
int findParent(int path[32][32], int size, int *cnt, int end);
int getWeight(int a_matrix[32][32], int size);

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

int isAppend(int path[32][32], int size, int index) {
    int countAppend = 0;
    for (int i = 0; i < size; i++) {
        if (path[index][i] != 0) {
            countAppend++;
        }
    }
    return countAppend == 1 ? 1 : 0;
}

int isAllAppended(int path[32][32], int size) {
    int countAppend = 0;
    for (int i = 0; i < size; i++) {
        if (isAppend(path, size, i)) {
            countAppend++;
        }
    }
    return countAppend == size ? 1 : 0;
}

int findMinWeight(int a_matrix[32][32], int path[32][32], int size, int index) {
    int min[2] = {-1, 10001}, flag = 0;

    for (int i = 0; i < size; i++) {
        if (a_matrix[index][i] != 0 && isAppend(path, size, index)) {
            if (a_matrix[index][i] < min[1]) {
                min[0] = i;
                min[1] = a_matrix[index][i];
                flag = 1;
            }
            if (a_matrix[index][i] == min[1]) {
                if (i < min[0]) {
                    min[0] = i;
                    min[1] = a_matrix[index][i];
                    flag = 1;
                }
            }
        }
    }

    return flag ? min[0] : -1;
}

int compareMinWeight(int a_matrix[32][32], int path[32][32], int size, int end_index, int start_index) {
    int end_min = findMinWeight(a_matrix[end_index], path, size);
    int start_min = findMinWeight(a_matrix[start_index], path, size);

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

}

