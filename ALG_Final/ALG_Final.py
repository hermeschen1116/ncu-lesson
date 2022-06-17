def get_edge_weight(weight_list_pram, start_node_pram, end_node_pram):
    return weight_list_pram[start_node_pram + end_node_pram]


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


def a_star(weight_list_pram, target_stage_pram):
    node_list = ['S', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I']
    open_queue = {'S': 0}
    closed_queue = {}
    total_weight = 0

    while len(open_queue):
        best_node = min(open_queue, key=open_queue.get)
        if get_stage(best_node) == target_stage_pram:
            return total_weight + open_queue[best_node]
        closed_queue[best_node] = open_queue[best_node]
        del open_queue[best_node]

    return total_weight


edge_list = ["SA", "SB", "SC", "AD", "AE", "AF", "BD", "BE", "BF", "CD", "CE", "CF", "DG", "DH", "DI", "EG", "EH", "EI",
             "FG", "FH", "FI", "GT", "HT", "IT"]
weight_list = []
for i in range(24):
    weight_list.append(int(input()))
graph = dict(zip(edge_list, weight_list))
target_stage = int(input())
print(a_star(weight_list, target_stage))
