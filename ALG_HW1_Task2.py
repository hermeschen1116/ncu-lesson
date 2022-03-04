from re import S


def isHappy (_src_) :
    bits = [ord(c)-48 for c in _src_]
    while len(bits) != 1 :
        sqr = str(sum([pow(bit, 2) for bit in bits]))
        bits = [ord(c)-48 for c in sqr]
    return True if bits[0] == 1 else False

n = int(input())
for i in range(n) :
    src = input()
    if isHappy(src) :
        print("Happy")
    else :
        print("Not Happy")