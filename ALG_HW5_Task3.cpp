#include <iostream>
#include <vector>
using namespace std;

void initializeMap(vector< vector<int> > &_map_, int sizeR, int sizeC);
void mapWalk(vector< vector<int> > &_map_, int sizeR, int sizeC);
void clearMap(vector< vector<int> > &_map_);

int main() {
    int nMap, m, n;
    vector< vector<int> > map;

    cin >> nMap;
    for (int i = 0; i < nMap; i++) {
        cin >> m >> n;
        mapWalk(map, m, n);
        cout << map[m-1][n-1] << endl;
        clearMap(map);
    }

    return 0;
}

void initializeMap(vector< vector<int> > &_map_, int sizeR, int sizeC) {
    vector<int> tmp;

    for (int i = 0; i < sizeR; i++) {
        if (i != 0) tmp.clear();
        for (int j = 0; j < sizeC; j++) {
            if (i == 0) tmp.push_back(1);
            else if (i != 0 && j == 0) tmp.push_back(1);
            else tmp.push_back(0);
        }
        _map_.push_back(tmp);
    }
}

void mapWalk(vector< vector<int> > &_map_, int sizeR, int sizeC) {
    initializeMap(_map_, sizeR, sizeC);
    for (int i = 1; i < sizeR; i++) {
        for (int j = 1; j < sizeC; j++) {
            _map_[i][j] += _map_[i-1][j] + _map_[i][j-1];
        }
    }
}

void clearMap(vector< vector<int> > &_map_) {
    for (int i = 0; i < _map_.size(); i++) _map_[i].clear();
    _map_.clear();
}