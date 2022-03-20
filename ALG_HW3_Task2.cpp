#include <iostream>

using namespace std;

void print_array(int _src_[]);

int main(void) {


    return 0;
}

void print_array(int _src_[]) {
    int length = sizeof(_src_)/sizeof(_src_[0]);

    cout << _src_[0];
    for (int i = 1; i < length; i++) {

    }
}