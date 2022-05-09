#include <iostream>
#include <vector>
using namespace std;

vector<int> steal(int _goal_, vector<int> _items_);
void showResult(vector<int> _pickUp_);

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
        showResult(steal(goal, items));
    }

    return 0;
}

vector<int> steal(int _goal_, vector<int> _items_) {
    int length = _items_.size(), tGoal;
    vector<int> get;

    if (length == 0) return get;
    sort(_items_.begin(), _items_.end(), greater<int>());
    for (int i = 0; i < length; i++) {
        get.clear();
        tGoal = 0;
        if (_items_[i] > _goal_) continue;
        for (int j = i; j < length; j++) {
            if (tGoal+_items_[j] <= _goal_) {
                tGoal += _items_[j];
                get.push_back(_items_[j]);
            }
            if (tGoal == _goal_) break;
        }
        if (tGoal == _goal_) break;
    }
    if (tGoal < _goal_) get.clear();

    return get;
}

void showResult(vector<int> _pickUp_) {
    int length = _pickUp_.size();

    if (length == 0) cout << "impossible" << endl;
    else {
        cout << _pickUp_[0];
        for (int i = 1; i < length; i++) cout << ' ' << _pickUp_[i];
        cout << endl;
    }
}