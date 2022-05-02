#include <iostream>
using namespace std;

void A(int _input_);
int B(int _input_);

int main(void) {
    char option;
    int input;

    while (cin >> option) {
        switch (option) {
            case 'A' :
                cin >> input;
                A(input);
                break;
            case 'B' :
                cin >> input;
                cout << B(input) << endl;
                break;
            default :
                cout << "Error!" << endl;
                continue;
        }
    }

    return 0;
}

void A(int _input_) {
    string num[8] = {"g ", "fu ", "nei ", "t ", "ra ", "bi ", "k ", "col "};
    int terms[8] = {50000000, 10000000, 1000000, 50000, 10000, 2500, 100, 10};
    int times[9] = {0}, curTerm = 0;
    times[8] = _input_;

    for (int i = 0; i < 8; i++) {
        if (times[8] == 33 || times[8] == 33333 || times[8] == 33333333) break;
        if (times[8] < terms[curTerm]) curTerm++;
        times[curTerm] += times[8] / terms[curTerm];
        times[8] %= terms[curTerm];
    }

    for (int i = 0; i < 9; i++) {
        if (times[i] == 0 || times[i] == 33 || times[i] == 33333 || times[i] == 33333333) continue;
        cout << times[i] << ' ';
        if (i != 8) cout << num[i];
    }
    cout << endl;
}

int B(int _input_) {
    int buffer = _input_;
    while (true) {
        switch (buffer % 5) {
            case 1 :
            case 4 :
                buffer *= 2;
                break;
            case 3 :
                buffer += 3;
                break;
            default : return buffer;
        }
    }
}