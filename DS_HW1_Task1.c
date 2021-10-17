#include<stdio.h>
#include<stdlib.h>

void swap(int *arr, int d);

int main(void) {
    int m, n, cnt = 0, tmp;
    int element, elements[10000][3];

    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &element);
            if (element != 0) {
                elements[cnt][0] = i;
                elements[cnt][1] = j;
                elements[cnt][2] = element;
                cnt++;
            }
        }
    }

    printf("Sparse matrix by triplet form:\n%d %d %d\n", m, n, cnt);
    for (int i = 0; i < cnt; i++) {
        printf("%d %d %d\n", elements[i][0], elements[i][1], elements[i][2]);
        tmp = elements[i][0];
        elements[i][0] = elements[i][1];
        elements[i][1] = tmp;
    }

    for (int i = 0; i < cnt; i++) {
        for (int j = cnt-1; j > i; j--) {
            if (elements[i][0] > elements[j][0]) {
                swap(&elements[i][0], j-i);
            }
            if (elements[i][0] == elements[j][0]) {
                if (elements[i][1] > elements[j][1]) {
                    swap(&elements[i][0], j-i);
                }
            }
        }
    }

    printf("Transpose of the sparse matrix:\n%d %d %d\n", m, n, cnt);
    for (int i = 0; i < cnt; i++) {
        printf("%d %d %d\n", elements[i][0], elements[i][1], elements[i][2]);
    }

    return 0;
}

void swap(int *arr, int d) {
    int tmp;
    for (int i = 0; i < 3; i++) {
        tmp = *(arr+i);
        *(arr+i) = *(arr+d*3+i);
        *(arr+d*3+i) = tmp;
    }
};