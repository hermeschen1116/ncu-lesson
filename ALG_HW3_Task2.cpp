#include <iostream>

using namespace std;

int cnt, src[1024];

void print_array(int _src_[], int _length_);
void swap(int *n1, int *n2);
void quick_sort(int _src_[], int _lb_, int _rb_);

int main(void) {
    int tmp;

    /*for (int i = 0; i < 8; i++) {
        cin >> src[i];
    }*/
    while (cin >> tmp) {
        src[cnt] = tmp;
        cnt++;
    }
    quick_sort(src, 0, 7);
    print_array(src, 8);

    return 0;
}

void print_array(int _src_[], int _length_) {
    cout << _src_[0];
    for (int i = 1; i < _length_; i++) {
        cout << " " << _src_[i];
    }
    cout << endl;
}

void swap(int *n1, int *n2) {
    int temp = *n1;

    *n1 = *n2;
    *n2 = temp;
}

void quick_sort(int _src_[], int _lb_, int _rb_) {
    int pivot = _rb_, l = _lb_, r = _rb_-1;
    if (_lb_ < _rb_) {
        while (true) {
            for (int i = l; i < _rb_; i++) {
                if (_src_[i] > _src_[pivot]) {
                    l = i;
                    break;
                }
            }
            for (int i = r; i >= _lb_; i--) {
                if (_src_[i] <= _src_[pivot]) {
                    r = i;
                    break;
                }
            }
            if (l < r) {
                swap(&_src_[l], &_src_[r]);
                print_array(_src_, cnt);
            } else {
                break;
            }
        }
        swap(&_src_[l], &_src_[pivot]);
        print_array(_src_, cnt);
        pivot = l;
        quick_sort(_src_, _lb_, pivot-1);
        quick_sort(_src_, pivot+1, _rb_);
    }
}