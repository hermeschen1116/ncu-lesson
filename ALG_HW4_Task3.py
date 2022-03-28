import math

def isPrime(n) :
    if n == 0 or n == 1 : return False
    bound = int(math.sqrt(n))
    for i in range(2, bound+1) :
        if n % i == 0 : return False
    return True

def buildPrimesTable(bound) :
    primesTable = list()
    for i in range(2, bound) :
        if isPrime(i) : primesTable.append(i)
    return primesTable

def countFactors(n, primesTable) :
    temp, length, nFactors = n, len(primesTable), 1
    
    if n == 1 : return 1
    if n in primesTable : return 2
    for i in range(length) :
        nCurFactor = 0
        while True :
            if temp % primesTable[i] != 0 : break
            else :
                temp = int(temp / primesTable[i])
                nCurFactor += 1
        nFactors *= nCurFactor + 1
    if nFactors == 1 : 
        primesTable.append(n)
    return nFactors

def findMostFactor(lb, rb) :
    primesTable = buildPrimesTable(65536)
    maximum = [0, 0]
    temp = 0

    if lb == rb : return lb, countFactors(lb, primesTable)
    for i in range(lb, rb+1) :
        temp = countFactors(i, primesTable)
        if temp > maximum[1] :
            maximum[0], maximum[1] = i, temp

    return maximum[0], maximum[1]

N = int(input())
for i in range(N) :
    L , U = map(int, input().split(' '))
    maxNum, maxFac = findMostFactor(L, U)
    print("Between {} and {}, {} has a maximum of {} divisors.".format(L, U, maxNum, maxFac))