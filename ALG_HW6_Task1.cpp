#include <iostream>
using namespace std;

int getStep(int _position_[]);

int main() {
    int position[4] = {0};
    int zCnt;

    while (true) {
        zCnt = 0;
        for (int i = 0; i < 4; i++) {
            cin >> position[i];
            if (position[i] == 0) ++zCnt;
        }
        if (zCnt == 4) break;
        cout << getStep(position) << endl;
    }

    return 0;
}

int getStep(int _position_[]) {
    if (_position_[0] == _position_[2] && _position_[1] == _position_[3]) return 0;
    if (_position_[0] == _position_[2] || _position_[1] == _position_[3] || abs(_position_[0] - _position_[2]) == abs(_position_[1] - _position_[3])) return 1;
    return 2;
}