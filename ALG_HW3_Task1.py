def print_array(_src_, _length_) :
    for i in range(_length_-1) :
        print(_src_[i], end=' ')
    print(_src_[_length_-1])

while True :
    n = int(input())
    if n == 0 :
        break
    data = list(map(int, input().split(' ')))
    print_array(sorted(data), n)