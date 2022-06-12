from math import sqrt, floor


def is_prime(test_prams):
    if test_prams == 0 or test_prams == 1:
        return False
    for i in range(2, floor(sqrt(test_prams)) + 1):
        if test_prams % i == 0:
            return False
    return True


def prime_factorize(src_prams):
    if src_prams == 0:
        return []
    if src_prams == 1:
        return [1]
    factor = []
    for i in range(2, floor(sqrt(src_prams)) + 1):
        buffer = [0, 0]
        if is_prime(i):
            buffer[0] = i
            while src_prams % i == 0:
                buffer[1] += 1
                src_prams = src_prams // i
            factor.append(buffer)
        if src_prams == 1:
            break
    return factor


def show_factor(src_prams, factor):
    print("{}=".format(src_prams), end="")
    for i in range(len(factor)):
        if factor[i][1] == 1:
            print("{}".format(factor[i][0]), end="")
        else:
            print("{}^{}".format(factor[i][0], factor[i][1]), end="")
        if i != len(factor) - 1:
            print("*", end="")
    print()


n = int(input())
show_factor(n, prime_factorize(n))
