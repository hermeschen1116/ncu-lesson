#include <iostream>
using namespace std;

long long int multiplyLast3Elements (long long int numElement);

int main () {
    int numInput;
    long long int numElement;

    cin >> numInput;
    for (int i = 0; i < numInput; i++) {
        cin >> numElement;
        if (numElement % 2 && numElement > 1 && numElement < 1000000000) {
            cout << multiplyLast3Elements(numElement) << endl;
        }
    }

    return 0;
}

long long int multiplyLast3Elements (long long int numElement) {
    long long int lineNum = (numElement+1) / 2;
    long long int lastElement = lineNum * lineNum * 2 - 1;
    return lastElement * (lastElement - 2) * (lastElement - 4);
}