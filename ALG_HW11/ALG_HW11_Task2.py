def max_cofactor(src_prams, test_prams):
    if src_prams % test_prams == 0:
        return test_prams
    else:
        return max_cofactor(test_prams, src_prams % test_prams)


def count_coprime(src_prams):
    count = 0
    for f in range(1, src_prams+1):
        if max_cofactor(src_prams, f) == 1:
            count += 1
    return count


for i in range(int(input())):
    src = int(input())
    print(count_coprime(src))
