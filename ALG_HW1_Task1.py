def isHappy (_src_) :
    _a_ += 1 if _a_ % 2 == 0 else 0
    _b_ -= 1 if _b_ % 2 == 0 else 0
    return int((_a_ + _b_) * ((_b_ - _a_) / 2 + 1) / 2)

n = int(input())
for i in range(n) :
    src = int(input())
