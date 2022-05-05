#include <iostream>
#include <vector>
using namespace std;

int getMinArrayDifference(vector<int> _array_);

int main() {
    int nData, arraySize, buffer;
    vector<int> array;

    cin >> nData;
    for (int i = 0; i < nData; i++) {
        array.clear();
        cin >> arraySize;
        for (int j = 0; j < arraySize; j++) {
            cin >> buffer;
            array.push_back(buffer);
        }
        cout << getMinArrayDifference(array) << endl;
    }

    return 0;
}

int getMinArrayDifference(vector<int> _array_) {
    int length = _array_.size();
    int left = 0, right = 0, minIndex = 0, minD, curD;

    if (length == 1) return 0;
    for (int i = 0; i < length; i++) right += _array_[i];
    minD = right;
    for (int i = 0; i < length; i++) {
        left += _array_[i];
        right -= _array_[i];
        curD = left / (i+1);
        if (i < length-1) curD = abs(curD - right / (length-i-1));
        if (curD < minD) {
            minD = curD;
            minIndex = i;
        }
        if (minD == 0) break;
    }

    return minIndex;
}