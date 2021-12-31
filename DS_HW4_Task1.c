#include<stdio.h>
#include<stdlib.h>

int **newEmptyMap(int **map, int n_rows, int n_columns);
void clearMap(int **map, int n_rows);
void findIsland(int r_Pos, int c_Pos, int **map, int n_rows, int n_columns);
int countIsland(int **map, int n_rows, int n_columns);

int main(void) {
    int nRows = 0, nColumns = 0, nIsland;
    int **map;

    scanf("%d %d", &nRows, &nColumns);
    map = newEmptyMap(map, nRows, nColumns);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    nIsland = countIsland(map, nRows, nColumns);
    printf("> %d\n", nIsland);
    clearMap(map, nRows);

    return 0;
}

int **newEmptyMap(int **map, int n_rows, int n_columns) {
    map = (int**)malloc(sizeof(int*)*n_rows);
    for (int i = 0; i < n_rows; i++) {
        map[i] = (int*)malloc(sizeof(int)*n_columns);
    }

    return map;
}

void clearMap(int **map, int n_rows) {
    for (int i = 0; i < n_rows; i++) {
        free(map[i]);
    }
    free(map);
}

void findIsland(int r_Pos, int c_Pos, int **map, int n_rows, int n_columns) {
    map[r_Pos][c_Pos] = -1;
    if (r_Pos-1 >= 0 && map[r_Pos-1][c_Pos] == 1) {
        findIsland(r_Pos-1, c_Pos, map, n_rows, n_columns);
    }
    if (r_Pos+1 < n_rows && map[r_Pos+1][c_Pos] == 1) {
        findIsland(r_Pos+1, c_Pos, map, n_rows, n_columns);
    }
    if (c_Pos-1 >= 0 && map[r_Pos][c_Pos-1] == 1) {
        findIsland(r_Pos, c_Pos-1, map, n_rows, n_columns);
    }
    if (c_Pos+1 < n_columns && map[r_Pos][c_Pos+1] == 1) {
        findIsland(r_Pos, c_Pos+1, map, n_rows, n_columns);
    }
}

int countIsland(int **map, int n_rows, int n_columns) {
    int count = 0;

    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_columns; j++) {
            if (map[i][j] == 1) {
                ++count;
                findIsland(i, j, map, n_rows, n_columns);
            }
        }
    }

    return count;
}