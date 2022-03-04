def title2Number (_title_) : 
    lsb = len(_title_)-1
    return sum([(ord(_title_[i])-64)*pow(26, lsb-i) for i in range(lsb, -1, -1)])

n = int(input())
for i in range(n) :
    title = input()
    print(title2Number(title))