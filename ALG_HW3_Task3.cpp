#include <iostream>
#include <string>

using namespace std;

int unsorted_degree(string _src_, int _length_);
void swap(int *n1, int *n2);
void sort_degree(int _degree_[][2], int _length_);
void print_data(string _src_[], int _degree_[][2], int _length_);

int main(void) {
    int q, n, m;
    string src[100];
    int degree[100][2];

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> n >> m;
        for (int j = 0; j < m; j++) {
            cin >> src[j];
            degree[j][0] = j;
            degree[j][1] = unsorted_degree(src[j], n);
        }
        sort_degree(degree, m);
        print_data(src, degree, m);
        if (i < q-1) {
            cout << endl;
        }
    }

    return 0;
}

int unsorted_degree(string _src_, int _length_) {
    int degree = 0;
    for (int i = 0; i < _length_; i++) {
        for (int j = 0; j < _length_; j++) {
            if ((j < i && _src_[j] > _src_[i]) || (j > i && _src_[j] < _src_[i])) {
                degree += 1;
            }
        }
    }
    return (int)degree/2;
}

void swap(int *n1, int *n2) {
    int temp;
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void sort_degree(int _degree_[][2], int _length_) {
    for (int i = 0; i < _length_; i++) {
        for (int j = i; j < _length_; j++) {
            if (_degree_[i][1] > _degree_[j][1]) {
                swap(_degree_[i][0], _degree_[j][0]);
                swap(_degree_[i][1], _degree_[j][1]);
            }
            if (_degree_[i][1] == _degree_[j][1] && _degree_[i][0] > _degree_[j][0]) {
                swap(_degree_[i][0], _degree_[j][0]);
                swap(_degree_[i][1], _degree_[j][1]);
            }
        }
    }
}

void print_data(string _src_[], int _degree_[][2], int _length_) {
    for (int i = 0; i < _length_; i++) {
        cout << _src_[_degree_[i][0]] << endl;
    }
}