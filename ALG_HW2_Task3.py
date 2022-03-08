from operator import le
import re
def isSubString(_testee_, _tester_) :
    testRE = "^\w*"
    for i in range(len(_testee_)) :
        testRE += _testee_[i] + "\w*"
    testRE += "$"
    
    return True if re.fullmatch(testRE, _tester_) != None else False


n = int(input())
for i in range(n) :
    s, t = input().split(" ")
    print("Yes" if isSubString(s, t) else "No")