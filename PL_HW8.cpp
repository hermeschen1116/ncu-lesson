#include <iostream>
#include <vector>
#include "matrix.h"

#define DIM_ROW 3
#define DIM_COL 3
#define arr1 { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} }
#define arr2 { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }

using namespace std;

template<int m, int n>
int **init(const int (&arr2d)[m][n]) {
    int **a = new int *[m];
    for (int i = 0; i < m; i++) {
        a[i] = new int[n];
        for (int j = 0; j < n; j++) {
            a[i][j] = arr2d[i][j];
        }
    }
    return a;
}

int main() {
    int **a1, **a2;
    a1 = init<DIM_ROW, DIM_COL>(arr1);
    a2 = init<DIM_ROW, DIM_COL>(arr2);
    Mat2D m1(a1, DIM_ROW, DIM_COL);
    Mat2D m2(a2, DIM_ROW, DIM_COL);

    Mat2D res{};
    // res = m1 + m2
    res = m1.add(m2);
    res.print();
    cout << endl;
    // res = m1 - m2
    res = m1.sub(m2);
    res.print();
    cout << endl;
    // res = 3*m1
    res = m1.scale(2);
    res.print();
    cout << endl;
    // res = m1 * m1
    res = m1.matmul(m2);
    res.print();
    cout << endl;
    // res = 3*m1 + 5*m2*m1
    res = m1.scale(3).add(m2.scale(5).matmul(m1));
    res.print();
}