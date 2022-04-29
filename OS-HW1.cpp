#include <iostream>
#include <string>
#include <thread>
using namespace std;

template <class T> void print_array(vector<T> _src_);
template <class T> void swap(T &n1, T &n2);
template <class T> void quick_sort(vector<T> _src_, int _lb_, int _rb_);

int main(void) {
    vector<int> src;


    return 0;
}

template <class T> void print_array(vector<T> _src_) {
    cout << _src_[0];
    for (int i = 1; i < _src_.size(); i++) {
        cout << " " << _src_[i];
    }
    cout << endl;
}

template <class T> void swap(T &n1, T &n2) {
    T temp = n1;

    n1 = n2;
    n2 = temp;
}

template <class T> void quick_sort(vector<T> _src_, int _lb_, int _rb_) {
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
                swap(_src_[l], _src_[r]);
            } else {
                break;
            }
        }
        swap(_src_[l], _src_[pivot]);
        pivot = l;
        quick_sort(_src_, _lb_, pivot-1);
        quick_sort(_src_, pivot+1, _rb_);
    }
}