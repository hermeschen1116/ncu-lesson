def print_array(_src_) :
    length = len(_src_)
    for i in range(length-1) :
        print(_src_[i], end=' ')
    print(_src_[length-1])

def find_element(_src_, _lb_, _rb_, pivot, dir = True) :
    if dir :
        for i in range(_lb_, _rb_) :
            if (_src_[i] > _src_[pivot]) :
                return int(i)
    else :
        for i in range(_rb_, _lb_-1, -1) :
            if (_src_[i] <= _src_[pivot]) :
                return int(i)

def quick_sort(_src_, _lb_, _rb_) :
    if _lb_ >= _rb_ :
        return 
    pivot, l, r = _rb_, _lb_, _rb_-1
    while True :
        print(_lb_, _rb_, l, r, pivot)
        l = find_element(_src_, l, _rb_, pivot, True)
        r = find_element(_src_, _lb_, r, pivot, False)
        if l < r :
            _src_[l], _src_[r] = _src_[r], _src_[l]
            print_array(_src_)
        else :
            break
    _src_[pivot], _src_[l] = _src_[l], _src_[pivot]
    print_array(_src_)
    quick_sort(_src_, _lb_, l-1)
    quick_sort(_src_, l+1, _rb_)
            

src = list(map(int, input().split(' ')))
quick_sort(src, 0, len(src)-1)
print_array(src)