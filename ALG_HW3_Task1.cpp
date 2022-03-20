#include <iostream>
#include <algorithm>

using namespace std;

void print_array(int _src_[], int _length_);

int main(void) {
    int years[2000000], length;

    while (true)
    {
        cin >> length;
        if (length == 0) {
            break;
        }
        for (int i = 0; i < length; i++) {
            cin >> years[i];
        }
        sort(years, years+length);
        print_array(years, length);
    }
    

    return 0;
}

void print_array(int _src_[], int _length_) {
    cout << _src_[0];
    for (int i = 1; i < _length_; i++) {
        cout << " " << _src_[i];
    }
    cout << endl;
}