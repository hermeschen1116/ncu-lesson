#include <iostream>
using namespace std;

int *getCardNumInput ();
bool validateCardNum (const int* cardNum);

int main () {
    int numInput;
    int* cardNum;

    cin >> numInput;
    for (int i = 0; i < numInput; i++) {
        cardNum = getCardNumInput();
        if (validateCardNum(cardNum)) cout << "Valid" << endl;
        else cout << "Invalid" << endl;
    }

    return 0;
}

int *getCardNumInput () {
    string textBuffer;
    int *cardNumBuffer = new int[16], cnt = 0;
    for (int i = 0; i < 4; i ++) {
        cin >> textBuffer;
        for (char num : textBuffer) cardNumBuffer[cnt++] = num - 48;
    }
    return cardNumBuffer;
}

bool validateCardNum (const int* cardNum) {
    int testCode = 0;
    for (int i = 0; i < 16; i++) {
        if (i % 2) testCode += cardNum[i];
        else testCode += (cardNum[i] * 2) % 10 + cardNum[i] * 2 / 10;
    }
    return testCode % 10 == 0;
}