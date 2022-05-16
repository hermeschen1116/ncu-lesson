// PL_HW8
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

class Mat2D {
public:
    Mat2D() = default;

    Mat2D(int **arr2D, int dim_row, int dim_col) {
        row = dim_row;
        column = dim_col;

        matrix = new int *[dim_row];
        if (arr2D != nullptr) {
            for (int i = 0; i < row; i++) {
                matrix[i] = new int[column];
                for (int j = 0; j < column; j++) matrix[i][j] = arr2D[i][j];
            }
        } else {
            for (int i = 0; i < row; i++) {
                matrix[i] = new int[column];
                for (int j = 0; j < column; j++) matrix[i][j] = 0;
            }
        }
    }

    Mat2D add(Mat2D m2) {
        Mat2D out(matrix, row, column);
        if (m2.column == column && m2.row == row) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) out.matrix[i][j] += m2.matrix[i][j];
            }
        }
        return out;
    }

    Mat2D sub(Mat2D m2) {
        Mat2D out(matrix, row, column);
        if (m2.column == column && m2.row == row) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) out.matrix[i][j] -= m2.matrix[i][j];
            }
        }
        return out;
    }

    Mat2D scale(int c) {
        Mat2D out(matrix, row, column);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) out.matrix[i][j] *= c;
        }
        return out;
    }

    Mat2D matmul(Mat2D m2) {
        Mat2D out(nullptr, row, m2.column);
        if (column == m2.row) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < m2.column; j++) {
                    for (int k = 0; k < column; k++) out.matrix[i][j] += matrix[i][k] * m2.matrix[k][j];
                }
            }
        }
        return out;
    }

    void print() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) cout << matrix[i][j] << ", ";
            cout << endl;
        }
    }

private:
    int row, column;
    int **matrix;
};

#endif /* MATRIX_H */