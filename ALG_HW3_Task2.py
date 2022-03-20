def print_array(_src_) :
    length = len(_src_)
    for i in range(length-1) :
        print(_src_[i], end=' ')
    print(_src_[length-1])

def partition(_src_, _lb_, _rb_) :
    swapped = False
    pivot = _rb_
    i = _lb_ - 1
    for j in range(_lb_, _rb_-1) :
        if _src_[pivot] >= _src_[j] :
            i = i+1
            _src_[i], _src_[j] = _src_[j], _src_[i]
            swapped = True
    _src_[_rb_], _src_[i+1] = _src_[i+1], _src_[_rb_]
    if swapped :
        print_array(_src_)
    return i+1

def quick_sort(_src_, _lb_, _rb_) :
    if _lb_ < _rb_ :
        pivot, l, r = _rb_, _lb_, _rb_-1

        while True :
            l = i for i in range(l, _rb_) if (_src_[i] ) >= _src_[pivot] else l
"""    if _lb_ < _rb_ :
        pivot = partition(_src_, _lb_, _rb_)
        quick_sort(_src_, _lb_, pivot-1)
        quick_sort(_src_, pivot+1, _rb_)"""


src = list(map(int, input().split(' ')))
quick_sort(src, 0, len(src)-1)
print_array(src)