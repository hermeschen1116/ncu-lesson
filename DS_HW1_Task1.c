#include<stdio.h>
#include<stdlib.h>

int main(void) {
    int m, n, cnt = 0, total = 0;
    int elements[100][100];


    scanf("%d %d", &m, &n);
    while (scanf("%d", &elements[total / n][total % n]) != EOF) {
        if (elements[total / n][total % n] != 0) {
            cnt++;
        }
        total++;
    }

    if (total != m * n) {
        printf("Input matrix has wrong size. Please input again.");
        return 0;
    }

    printf("Sparse matrix by triplet form:\n%d %d %d\n", m, n, cnt);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (elements[i][j] != 0) {
                printf("%d %d %d\n", i, j, elements[i][j]);
            }
        }
    }

    printf("Transpose of the sparse matrix:\n%d %d %d\n", n, m, cnt);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (elements[j][i] != 0) {
                printf("%d %d %d\n", i, j, elements[j][i]);
            }
        }
    }

    return 0;
}