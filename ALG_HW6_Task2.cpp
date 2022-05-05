#include <iostream>
#include <vector>
using namespace std;

vector<int> pickUp(int _goal_, vector<int> _items_);
void getResult(vector<int> _get_);

int main() {
    int nData, goal, nItem, buffer;
    vector<int> items;

    cin >> nData;
    for (int i = 0; i < nData; i++) {
        items.clear();
        cin >> goal >> nItem;
        for (int j = 0; j < nItem; j++) {
            cin >> buffer;
            items.push_back(buffer);
        }
        getResult(pickUp(goal, items));
    }

    return 0;
}

vector<int> pickUp(int _goal_, vector<int> _items_) {
    int length = _items_.size(), tGoal = 0;
    int pick[length+1][_goal_+1];
    vector<int> get;

    sort(_items_.begin(), _items_.end(), greater<int>());
    for (int i = 0; i <= _goal_; i++) pick[0][i] = 0;
    for (int i = 1; i <= length; i++) {
        for (int j = 0; j <= _goal_; j++) {
            if (_items_[j] < i)
        }
    }

    return get;
}

void getResult(vector<int> _get_) {
    int length = _get_.size();

    if (length == 0) cout << "impossible" << endl;
    else {
        cout << _get_[0];
        for (int i = 1; i < length; i++) cout << ' ' << _get_[i];
        cout << endl;
    }
}