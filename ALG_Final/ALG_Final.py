def get_edge_weight(graph_pram, start_node_pram, end_node_pram):
    return graph_pram[start_node_pram + end_node_pram]


def get_children(start_node_pram, graph_pram):
    node_list = ['S', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'T']

    children = []
    for node in node_list:
        if start_node_pram + node not in graph_pram.keys():
            continue
        children.append(node)
    return children


def get_min_child(node_pram, graph_pram, closed_queue_pram):
    min_child = []
    for child in get_children(node_pram, graph_pram):
        if child in closed_queue_pram.keys():
            continue
        min_child.append(get_edge_weight(graph_pram, node_pram, child))
    if len(min_child) == 0:
        return 0
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


def a_star(graph_pram, target_stage_pram):
    node_list = ['S', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'T']
    open_queue = {'S': [0, get_min_child('S', graph_pram, {})]}
    closed_queue = {}

    if target_stage_pram < 1 or target_stage_pram > 5:
        return None
    if target_stage_pram == 1:
        return sum(open_queue['S'])
    while len(open_queue):
        best_node = min(open_queue, key=lambda x: sum(open_queue[x]))
        node_list.remove(move_node(best_node, open_queue, closed_queue))
        if get_stage(best_node) == target_stage_pram:
            return sum(closed_queue[best_node])
        for child in get_children(best_node, graph_pram):
            if child in closed_queue.keys():
                continue
            evaluation = [closed_queue[best_node][0] + get_edge_weight(graph_pram, best_node, child),
                          get_min_child(child, graph_pram, closed_queue)]
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
