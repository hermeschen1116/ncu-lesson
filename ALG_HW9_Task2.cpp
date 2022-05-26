#include <iostream>
#include <vector>
using namespace std;

bool emptyStorage (const vector<int>& storageState);
int countNeedyBox (vector<int> storageState);

int main() {
    vector<int> storageState(6, 0);

    while (true) {
        for (int &good : storageState) cin >> good;
        if (emptyStorage(storageState)) break;
        cout << countNeedyBox(storageState) << endl;
    }
    return 0;
}

bool emptyStorage (const vector<int>& storageState) {
    for (int good : storageState) {
        if (good != 0) return false;
    }
    return true;
}

int countNeedyBox (vector<int> storageState) {
    int totalBox = storageState[5] + storageState[4] + storageState[3];
    int tmp;

    storageState[0] -= 11 * storageState[4];
    if (storageState[0] < 0) storageState[0] = 0;

    tmp = storageState[1] - 5 * storageState[3];
    if (tmp < 0) {
        tmp *= (-1);
        if (storageState[0] != 0) storageState[0] -= 4 * tmp;
        if (storageState[0] < 0) storageState[0] = 0;
        storageState[1] = 0;
    } else storageState[1] = tmp;

    totalBox += storageState[2] / 4;
    storageState[2] %= 4;
    if (storageState[2] != 0) {
        ++totalBox;
        tmp = storageState[1];
        if (tmp != 0) {
            if (storageState[2] == 3) tmp -= 1;
            else if (storageState[2] == 2) tmp -= 3;
            else tmp -= 5;
            storageState[1] = tmp > 0 ? tmp : 0;
            if (tmp < 0) tmp *= (-1);
        }
        if (storageState[0] > 0)
        {
            if (storageState[2] == 3) storageState[0] -= 5;
            else if (storageState[2] == 2) storageState[0] -= 6;
            else storageState[0] -= 7;
            storageState[0] -= tmp * 4;
        }
    }
    storageState[2] = 0;

    totalBox += storageState[1] / 9;
    storageState[1] %= 9;
    if (storageState[1] != 0) {
        ++totalBox;
        storageState[0] -= 36 - 4 * storageState[1];
        if (storageState[0] < 0) storageState[0] = 0;
    }

    totalBox += storageState[0] / 36;
    storageState[0] %= 36;
    if (storageState[0] != 0) {
        ++totalBox;
        storageState[0] = 0;
    }

    return totalBox;
}