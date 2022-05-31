def get_least_move(bricks_list):
    avg_height = int(sum(bricks_list) / len(bricks_list))
    return int(sum(abs(brick - avg_height) for brick in bricks_list) / 2)


for i in range(int(input())):
    nBricks = int(input())
    bricks = list(map(int, input().split(' ')))
    print(get_least_move(bricks))
