#include<stdio.h>

int isConnected(int a_matrix[128][128], int size);
void showAdjacencyMatrix(int a_matrix[][128], int size);
void swap(int *data_1, int *data_2);
void swapEdge(int edge_1[3], int edge_2[3]);
void sortEdges(int edges[128][3], int size);
int isAllAppended(int status[128], int size);
int getWeight(int edges_list[128][3], int line, int size);

int main(void) {
    int size, line, edgeList[128][3] = {0}, aMatrix[128][128] = {0}, weight;

    scanf("%d %d", &size, &line);
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &edgeList[i][j]);
        }
        aMatrix[edgeList[i][0]][edgeList[i][1]] = edgeList[i][2];
        aMatrix[edgeList[i][1]][edgeList[i][0]] = edgeList[i][2];
    }

    if (isConnected(aMatrix, size)) {
        weight = getWeight(edgeList, line, size);
        printf("> %d\n", weight);
    } else {
        printf("> NO connected\n");
    }
    showAdjacencyMatrix(aMatrix, size);

    return 0;
}

int isConnected(int a_matrix[128][128], int size) {
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

void showAdjacencyMatrix(int a_matrix[][128], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", a_matrix[i][0]);
        for (int j = 1; j < size; j++) {
            printf(" %d", a_matrix[i][j]);
        }
        printf("\n");
    }
}

void swap(int *data_1, int *data_2) {
    int temp;

    temp = *data_1;
    *data_1 = *data_2;
    *data_2 = temp;
}

void swapEdge(int edge_1[3], int edge_2[3]) {
    for (int i = 0; i < 3; i++) {
        swap(&edge_1[i], &edge_2[i]);
    }
}

void sortEdges(int edges[128][3], int line) {
    for (int i = 0; i < line; i++) {
        for (int j = line-1; j > i; j--) {
            if (edges[i][2] > edges[j][2]) {
                swapEdge(edges[i], edges[j]);
            }
        }
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

int getWeight(int edges_list[128][3], int line, int size) {
    int status[128] = {0}, weight, start, end;

    sortEdges(edges_list, line);
    for (int i = 0; i < line; i++) {
        start = status[edges_list[i][0]];
        end = status[edges_list[i][1]];
        if (isAllAppended(status, size) == 0) {
            if (start*end == 0) {
                if (start - end == 0) {
                    weight += edges_list[i][2];
                    status[edges_list[i][0]] = 1;
                    status[edges_list[i][1]] = 1;
                }
                if (start - end == -1) {
                    weight += edges_list[i][2];
                    status[edges_list[i][0]] = 1;
                }
                if (start - end == 1) {
                    weight += edges_list[i][2];
                    status[edges_list[i][1]] = 1;
                }
            }
        }
    }

    return weight;
}


