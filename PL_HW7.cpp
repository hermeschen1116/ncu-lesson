#include <iostream>
#include <vector>
using namespace std;

vector< vector<char> > initializeCanvas(int _nRow_, int _nColumn_);
void turn(int &_direction_, char _turn_);
void move(int _position_[], int _direction_, int _step_, int _nRow_, int _nColumn_);
void draw(vector< vector<char> > &_canvas_, int _position_[], int _direction_, int _step_);
void showCanvas(vector< vector<char> > _canvas_);

int main () {
    vector< vector<char> > canvas = initializeCanvas(10, 10);
    char option;
    int step, direction = 0;
    int position[2] = {0, 0};
    bool controlSign = false;

    while (true) {
        cin >> option;
        if (option == 'E') break;
        switch (option) {
            case 'U' :
                controlSign = false;
                break;
            case 'D' :
                controlSign = true;
                canvas[position[0]][position[1]] = '*';
                break;
            case 'L' :
            case 'R' :
                turn(direction, option);
                break;
            case 'W' :
                cin >> step;
                if (controlSign) draw(canvas, position, direction, step);
                else move(position, direction, step, 10, 10);
        }
    }

    showCanvas(canvas);

    return 0;
}

vector< vector<char> > initializeCanvas(int _nRow_, int _nColumn_) {
    vector< vector<char> > canvas;
    vector<char> tmp;

    for (int i = 0; i < _nColumn_; i++) tmp.push_back('-');
    for (int i = 0; i < _nRow_; i++) canvas.push_back(tmp);

    return canvas;
}

void turn(int &_direction_, char _turn_) {
    if (_turn_ == 'L') {
        if (_direction_ == 0) _direction_ =  3;
        else _direction_ =  (_direction_-1) % 4;
    }
    else _direction_ = (_direction_+1) % 4;
}

void move(int _position_[], int _direction_, int _step_, int _nRow_, int _nColumn_) {
    for (int i = 0; i < _step_; i++) {
        switch (_direction_) {
            case 0 :
                if (_position_[0]-1 < 0) break;
                --_position_[0];
                break;
            case 1 :
                if (_position_[1]+1 >= _nColumn_) break;
                ++_position_[1];
                break;
            case 2 :
                if (_position_[0]+1 >= _nRow_) break;
                ++_position_[0];
                break;
            case 3 :
                if (_position_[1]-1 < 0) break;
                --_position_[1];
        }
    }
}

void draw(vector< vector<char> > &_canvas_, int _position_[], int _direction_, int _step_) {
    int nRow = _canvas_.size();
    int nColumn = _canvas_[0].size();

    for (int i = 0; i < _step_; i++) {
        switch (_direction_) {
            case 0 :
                if (_position_[0]-1 < 0) break;
                _canvas_[_position_[0]][_position_[1]] = '*';
                --_position_[0];
                break;
            case 1 :
                if (_position_[1]+1 >= nColumn) break;
                _canvas_[_position_[0]][_position_[1]] = '*';
                ++_position_[1];
                break;
            case 2 :
                if (_position_[0]+1 >= nRow) break;
                _canvas_[_position_[0]][_position_[1]] = '*';
                ++_position_[0];
                break;
            case 3 :
                if (_position_[1]-1 < 0) break;
                _canvas_[_position_[0]][_position_[1]] = '*';
                --_position_[1];
        }
    }
}


void showCanvas(vector< vector<char> > _canvas_) {
    int nRow = _canvas_.size();
    int nColumn = _canvas_[0].size();

    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nColumn; j++) cout << _canvas_[i][j];
        cout << endl;
    }
}