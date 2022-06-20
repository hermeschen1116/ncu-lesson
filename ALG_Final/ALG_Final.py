def get_edge_weight(weight_list_pram, start_node_pram, end_node_pram):
    return weight_list_pram[start_node_pram + end_node_pram]


def get_children(start_node_pram, weight_list_pram):
    node_list = ['S', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I']

    children = []
    for node in node_list:
        if start_node_pram + node not in weight_list_pram.keys():
            continue
        children.append(node)
    return children


def get_min_child(node_pram, weight_list_pram, closed_queue_pram):
    min_child = []
    for child in get_children(node_pram, weight_list_pram):
        if child in closed_queue_pram.keys():
            continue
        min_child.append(get_edge_weight(weight_list_pram, node_pram, child))
    return min(min_child)


def get_stage(node_pram):
    if node_pram == 'S':
        return 1
    elif 'A' <= node_pram <= 'C':
        return 2
    elif 'D' <= node_pram <= 'F':
        return 3
    elif 'G' <= node_pram <= 'I':
        return 4
    else:
        return 5


def move_node(node_pram, open_queue_pram, closed_queue_pram):
    closed_queue_pram[node_pram] = open_queue_pram[node_pram]
    del open_queue_pram[node_pram]
    return node_pram


def a_star(weight_list_pram, target_stage_pram):
    node_list = ['S', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I']
    open_queue = {'S': [0, 0]}
    closed_queue = {}

    open_queue['S'][1] = get_min_child('S', weight_list_pram, closed_queue)
    while len(open_queue):
        best_node = min(open_queue, key=lambda x: sum(open_queue[x]))
        node_list.remove(move_node(best_node, open_queue, closed_queue))
        if get_stage(best_node) == target_stage_pram:
            return sum(closed_queue[best_node])
        for child in get_children(best_node, weight_list_pram):
            if child in closed_queue.keys():
                continue
            evaluation = [sum(closed_queue[best_node]), get_min_child(child, weight_list_pram, closed_queue)]
            if child in open_queue.keys() and evaluation[0] > open_queue[child][0]:
                continue
            open_queue[child] = evaluation


edge_list = ["SA", "SB", "SC", "AD", "AE", "AF", "BD", "BE", "BF", "CD", "CE", "CF", "DG", "DH", "DI", "EG", "EH", "EI",
             "FG", "FH", "FI", "GT", "HT", "IT"]
for i in range(int(input())):
    weight_list = []
    for j in range(24):
        weight_list.append(int(input()))
    graph = dict(zip(edge_list, weight_list))
    target_stage = int(input())
    print(a_star(graph, target_stage))
