#include <iostream>
#include <cmath>
using namespace std;

void SumSquare ();

int main() {
    SumSquare();

    return 0;
}

void SumSquare () {
    short input;
    short sum = 0;

    try {
        while (cin >> input) {
            if (input >= -128 && input <= 128) {
                sum += (short) pow(input, 2);
            } else throw "Overflow";
        }
    } catch (out_of_range &e) {
        cout << "Out of Range" << endl;
    }
    cout << sum << endl;
}