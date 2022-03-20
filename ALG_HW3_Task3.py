def unsort_degree(_src_) :
    length = len(_src_)
    degree = 0
    for i in range(length) :
        for j in range(length) :
            if (j < i and _src_[j] > _src_[i]) or (j > i and _src_[j] < _src_[i]) :
                degree += 1
    return int(degree/2)

def print_data(_data_) :
    for i in range(len(_data_)) :
        data = sorted(_data_[i], key=lambda d: d[1])
        for j in range(len(data)) :
            print(data[j][0])
        print()

q = int(input())
data = list()
for i in range(q) :
    n, m = map(int, input().split(' '))
    data.append(list())
    for j in range(m) :
        src = input()
        data[i].append([src, unsort_degree(src)])
    print()
print_data(data)