def minUNext(uglyNumbers, nextUNumber) :
    minIndex, minimum = 0, nextUNumber[0][0]*uglyNumbers[nextUNumber[0][1]]
    for i in range(1,3) :
        cur = nextUNumber[i][0]*uglyNumbers[nextUNumber[i][1]]
        if cur < minimum :
            minIndex, minimum = i, cur
    return minIndex, minimum
1
def nthUglyNumber(nth) :
    if nth <= 1 : return 1
    uglyNumbers = [1]
    nextUNumber = [[2, 0], [3, 0], [5, 0]]
    while len(uglyNumbers) < nth :
        if len(uglyNumbers) == nth : break
        minIndex, minimum = minUNext(uglyNumbers, nextUNumber)
        if minimum not in uglyNumbers : uglyNumbers.append(minimum)
        nextUNumber[minIndex][1] += 1
    return uglyNumbers[-1]


K = int(input())
for i in range(K) :
    N = int(input())
    print(nthUglyNumber(N))