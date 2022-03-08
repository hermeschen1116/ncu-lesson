def fibonacci(n) :
    if n == 0 or n == 1 :
        return n
    else :
        return fibonacci(n-1)+fibonacci(n-2)

k = int(input())
for i in range(k) :
    print(fibonacci(int(input())))