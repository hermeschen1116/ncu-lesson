#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void splitFormula(string _formula_, string &_lhs_, string &_rhs_);
int locateSymbol(string _formula_, int _start_);
int getConstant(string _buffer_);
void simplifyFormula(string _ohs_, int _constant_[]);
pair<int, int> evaluateFormula(string _formula_);
void showFormulaAnswer(string _formula_);

int main() {
    int nFormula;
    string formula;

    cin >> nFormula;
    for (int i = 0; i < nFormula; i++) {
        cin >> formula;
        showFormulaAnswer(formula);
    }

    return 0;
}

void splitFormula(string _formula_, string &_lhs_, string &_rhs_) {
    int equalIndex = _formula_.find("=");

    _lhs_ = _formula_.substr(0, equalIndex);
    _rhs_ = _formula_.substr(equalIndex+1);
}

int locateSymbol(string _formula_, int _start_) {
    int length = _formula_.size();

    if (_start_ >= length && _start_ < 0) return -1;
    for (int i = _start_; i < length; i++) {
        if ((_formula_[i] == '+' || _formula_[i] == '-') && i != _start_) return i;
    }
    return length;
}

int getConstant(string _buffer_) {
    if (_buffer_ == "+" || _buffer_ == "-") _buffer_ += '1';
    return _buffer_.size() != 0 ? stoi(_buffer_) : 1;
}

void simplifyFormula(string _ohs_, int _constant_[]) {
    int length = _ohs_.size(), target, start = 0, segLen;

    for (int i = 0; i < length; i++) {
        if (i >= start) {
            target = locateSymbol(_ohs_, start);
            if (target == -1) break;
            segLen = target - start;
            if (_ohs_[target-1] == 'x') _constant_[0] += getConstant(_ohs_.substr(start, segLen - 1));
            else _constant_[1] += getConstant(_ohs_.substr(start, segLen));
            start = target;
        }
    }
}

pair<int, int> evaluateFormula(string _formula_) {
    string lhs, rhs;
    int lhsConstant[2] = {0}, rhsConstant[2] = {0};
    pair<int, int> constant;

    splitFormula(_formula_, lhs, rhs);
    simplifyFormula(lhs, lhsConstant);
    simplifyFormula(rhs, rhsConstant);
    if (lhsConstant[0] > rhsConstant[0]) {
        constant.first = lhsConstant[0] - rhsConstant[0];
        constant.second = rhsConstant[1] - lhsConstant[1];
    } else {
        constant.first = rhsConstant[0] - lhsConstant[0];
        constant.second = lhsConstant[1] - rhsConstant[1];
    }

    return constant;
}

void showFormulaAnswer(string _formula_) {
    pair<int, int> constant = evaluateFormula(_formula_);

    if (constant.first == constant.second) cout << "IDENTITY" << endl;
    else if (constant.first == 0 && constant.second != 0) cout << "IMPOSSIBLE" << endl;
    else cout << floor((double)constant.second / constant.first) << endl;
}
