def find_next_roof(floor_list, roof):
    for f in floor_list:
        if f > roof:
            return f
    return None


def build_tower(red_floor_list, blue_floor_list):
    red_floor_list.sort()
    blue_floor_list.sort()
    roof = [0, 0]
    control_signal = 0 if red_floor_list[0] < blue_floor_list[0] else 1
    none_signal = 0
    while True:
        tmp_roof = roof[0]
        if control_signal % 2 == 0:
            roof[0] = find_next_roof(red_floor_list, roof[0])
        else:
            roof[0] = find_next_roof(blue_floor_list, roof[0])
        if roof[0] is None:
            roof[0] = tmp_roof
            none_signal += 1
        else:
            roof[1] += 1
            control_signal += 1
        if none_signal == 2:
            break

    return roof[1]


for i in range(int(input())):
    red_floors = []
    blue_floors = []
    for j in range(int(input())):
        floor = int(input())
        if floor < 0:
            red_floors.append(abs(floor))
        else:
            blue_floors.append(floor)
    print(build_tower(red_floors, blue_floors))
