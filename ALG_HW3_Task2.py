def print_array(_src_) :
    length = len(_src_)
    for i in range(length-1) :
        print(_src_[i], end=' ')
    print(_src_[length-1])

def quick_sort(_src_, _lb_, _rb_) :
    if _lb_ < _rb_ :
        pivot, l, r = _src_[_rb_], _lb_, _rb_-1
        while True :
            while l < _rb_ and _src_[l] < pivot : l += 1
            while r > 0 and _src_[r] > pivot : r -= 1
            if l >= r :
                break
            _src_[l], _src_[r] = _src_[r], _src_[l]
            if l != r : print_array(_src_)
        _src_[_rb_], _src_[l] = _src_[l], _src_[_rb_]
        if _rb_ != l : print_array(_src_)
        quick_sort(_src_, _lb_, l-1)
        quick_sort(_src_, l+1, _rb_)
            

src = list(map(int, input().split(' ')))
print_array(src)
quick_sort(src, 0, len(src)-1)