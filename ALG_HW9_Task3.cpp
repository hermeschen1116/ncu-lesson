#include <iostream>
using namespace std;

int multiplyLast3Elements (int numElement);

int main () {
    int numInput, numElement;

    cin >> numInput;
    for (int i = 0; i < numInput; i++) {
        cin >> numElement;
        cout << multiplyLast3Elements(numElement) << endl;
    }

    return 0;
}

int multiplyLast3Elements (int numElement) {
    int lastElement = 1 + 2 * ((numElement + 3) * ((numElement-1) / 2) / 2);
    return lastElement * (lastElement - 2) * (lastElement - 4);
}