#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

bool pointsCompareX(pair<int, int> _point1_, pair<int, int> _point2_);
bool pointsCompareY(pair<int, int> _point1_, pair<int, int> _point2_);
bool pointsCompare(pair<int, int> _point1_, pair<int, int> _point2_);
double calculateDistance(pair<int, int> _point1_, pair<int, int> _point2_);
pair<int, int> getCentralBound(vector< pair<int, int> > _src_, int _lb_, int _rb_, double _dMin_);
double findClosestDistanceC(vector< pair<int, int> > _src_, int _lb_, int _rb_, double _dMin_);
double findClosestDistance(vector< pair<int, int> > _src_, int _lb_, int _rb_);
double findClosestDistance(vector< pair<int, int> > &_src_);

int main() {
    int n, m;
    int xI, yI;
    vector< pair<int, int> > points;

    cin >> n;
    for (int i = 0; i < n; i++) {
        points.clear();
        cin >> m;
        for (int j = 0; j < m; j++) {
            cin >> xI >> yI;
            points.push_back(make_pair(xI, yI));
        }
        sort(points.begin(), points.end(), pointsCompare);
        printf("%.3lf\n", findClosestDistance(points));
    }

    return 0;
}

bool pointsCompareX(pair<int, int> _point1_, pair<int, int> _point2_) {
    return _point1_.first < _point2_.first ? true : false;
}

bool pointsCompareY(pair<int, int> _point1_, pair<int, int> _point2_) {
    return _point1_.second < _point2_.second ? true : false;
}

bool pointsCompare(pair<int, int> _point1_, pair<int, int> _point2_) {
    if (_point1_.first != _point2_.first) return pointsCompareX(_point1_, _point2_);
    else return pointsCompareY(_point1_, _point2_);
}

double calculateDistance(pair<int, int> _point1_, pair<int, int> _point2_) {
    int dx = _point1_.first - _point2_.first;
    int dy = _point1_.second - _point2_.second;
    int ds = pow(dx, 2) + pow(dy, 2);

    return sqrt(ds);
}

pair<int, int> getCentralBound(vector< pair<int, int> > _src_, int _lb_, int _rb_, double _dMin_) {
    int l = _lb_, r = _rb_;
    int length = _rb_ - _lb_ + 1;
    int mid = (_lb_ + _rb_) / 2;
    double xp = _src_[mid].first, range;

    if (length % 2 == 0) xp = (xp + _src_[mid+1].first) / 2;

    range = xp - _dMin_;
    for (int i = _lb_; i <= _rb_; i++) {
        if (_src_[i].first >= range) {
            l = i;
            break;
        }
    }
    range = xp + _dMin_;
    for (int i = _rb_; i >= _lb_; i--) {
        if (_src_[i].first <= range) {
            r = i;
            break;
        }
    }

    return make_pair(l, r);
}

double findClosestDistanceC(vector< pair<int, int> > _src_, int _lb_, int _rb_, double _dMin_) {
    pair<int, int> bound = getCentralBound(_src_, _lb_, _rb_, _dMin_);
    int length = bound.second - bound.first + 1;
    int left = (_lb_ + _rb_) / 2, right = left;
    double tmp, min = _dMin_;
    pair<double, double> range;

    if (length == 2) return calculateDistance(_src_[bound.first], _src_[bound.second]);

    if (_src_.size() % 2 == 0) right += 1;
    vector< pair<int, int> > leftPart(&_src_[bound.first], &_src_[left+1]);
    vector< pair<int, int> > rightPart(&_src_[right], &_src_[bound.second+1]);
    sort(rightPart.begin(), rightPart.end(), pointsCompareY);
    for (int i = 0; i < leftPart.size(); i++) {
        range.first = leftPart[i].second - min;
        range.second = leftPart[i].second + min;
        for (int j = 0; j < rightPart.size(); j++) {
            if (rightPart[j].second >= range.first && rightPart[j].second <= range.second) {
                tmp = calculateDistance(leftPart[i], rightPart[j]);
                if (tmp < min) min = tmp;
            }
        }
    }

    return min;
}

double findClosestDistance(vector< pair<int, int> > _src_, int _lb_, int _rb_) {
    int length = _rb_ - _lb_ + 1;
    int left = (_lb_ + _rb_) / 2, right;
    double lMin, rMin, cMin, min;

    if (length == 2) return calculateDistance(_src_[_lb_], _src_[_rb_]);

    if (length % 2) right = left;
    else right = left + 1;

    lMin = findClosestDistance(_src_, _lb_, left);
    rMin = findClosestDistance(_src_, right, _rb_);
    min = lMin < rMin ? lMin : rMin;
    cMin = findClosestDistanceC(_src_, _lb_, _rb_, min);
    min = cMin < min ? cMin : min;

    return min;
}

double findClosestDistance(vector< pair<int, int> > &_src_) {
    sort(_src_.begin(), _src_.end(), pointsCompare);
    return findClosestDistance(_src_, 0, _src_.size()-1);
}