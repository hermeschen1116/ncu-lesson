def bubble_sort(_src_, _length_) :
    for i in range(_length_) :
        for j in range(i, _length_) :
            if (_src_[i] > _src_[j]) :
                _src_[i], _src_[j] = _src_[j], _src_[i]

def print_array(_src_, _length_) :
    for i in range(_length_-1) :
        print(_src_[i], end=' ')
    print(_src_[_length_-1])

while True :
    n = int(input())
    if n == 0 :
        break
    data = list(map(int, input().split(' ')))
    bubble_sort(data, n)
    print_array(data, n)