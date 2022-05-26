#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool emptyStorage (const vector<int>& storageState);
int pickGood (const vector<int>& storageState, int restBoxSize);
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

int pickGood (const vector<int>& storageState, const int restBoxSize) {
    for (int i = 5; i >= 0; i--) {
        if (storageState[i] != 0 && i+1 <= restBoxSize) return i;
    }
    return -1;
}

int countNeedyBox (vector<int> storageState) {
    vector<int> goodArea;
    int leftArea;
    int leftSize;
    int curGood;
    int totalBox = 0;

    for (int i = 1; i < 7; i++) goodArea.push_back((int) pow(i, 2));
    while (!emptyStorage(storageState)) {
        leftArea = (int) pow(6, 2);
        leftSize = 6;
        while (leftArea > 0) {
            curGood = pickGood(storageState, leftSize);
            //cout << curGood+1 << ":" << leftArea << " ";
            if (curGood == -1) break;
            if (leftArea - goodArea[curGood] >= 0) {
                leftArea -= goodArea[curGood];
                --storageState[curGood];
            } else {
                if (leftSize - curGood + 1 >= 0) leftSize -= curGood + 1;
                else break;
            }
            //cout << curGood+1 << ":" << leftArea << " ";
        }
        //cout << "total:" << totalBox << endl;
        totalBox++;
    }

    return totalBox;
}