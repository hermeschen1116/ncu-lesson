def swapCount(_arr_, _q_) :
    swapCnt = 0
    for i in range(_q_) :
        for j in range(i, _q_) :
            if (_arr_[i] > _arr_[j]) :
                _arr_[i], _arr_[j] = _arr_[j], _arr_[i]
                swapCnt += 1
    return swapCnt

n = int(input())
for i in range(n) :
    q = int(input())
    src = list(map(int, input().split(' ')))
    print("Optimal swapping takes {} swaps.".format(swapCount(src, q)))