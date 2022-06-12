for quest in range(int(input())):
    grades = list(map(int, input().split()))
    rank = int(input())
    grades.sort()
    print(grades[rank-1])
