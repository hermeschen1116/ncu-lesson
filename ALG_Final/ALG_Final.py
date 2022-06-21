def get_edge_weight(graph_pram, start_node_pram, end_node_pram):  # get the weight of the edge
    if start_node_pram + end_node_pram not in graph_pram.keys():  # if the edge doesn't exist
        return float('inf')
    return graph_pram[start_node_pram + end_node_pram]


def get_children(start_node_pram, graph_pram):  # get the children of the node
    node_list = ['S', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'T']

    children = []
    for node in node_list:
        if start_node_pram + node not in graph_pram.keys():  # if the edge doesn't exist
            continue
        children.append(node)
    return children


def get_min_child(node_pram, graph_pram, closed_queue_pram):  # get the minimum child of the node and its weight
    min_child = []
    for child in get_children(node_pram, graph_pram):  # get the children of the node
        if child in closed_queue_pram.keys():  # if the child has been visited
            continue
        min_child.append(get_edge_weight(graph_pram, node_pram, child))  # get the weight of the edge
    if len(min_child) == 0:  # if the node has no children
        return 0
    return min(min_child)


def get_stage(node_pram):  # get the stage of the node
    if node_pram == 'S':
        return 1
    elif 'A' <= node_pram <= 'C':
        return 2
    elif 'D' <= node_pram <= 'F':
        return 3
    elif 'G' <= node_pram <= 'I':
        return 4
    elif node_pram == 'T':
        return 5
    else:
        return None  # if the node is not in the node list


def a_star(graph_pram, target_stage_pram):  # A* algorithm
    open_queue = {'S': [0, get_min_child('S', graph_pram, {})]}  # initialize the open queue
    closed_queue = {}  # initialize the closed queue

    if target_stage_pram < 1 or target_stage_pram > 5:  # if the target stage is out of range
        return None
    while len(open_queue):
        best_node = min(open_queue, key=lambda x: sum(open_queue[x]))  # get the best node
        closed_queue[best_node] = open_queue[best_node]
        del open_queue[best_node]  # move the node from open to closed
        if get_stage(best_node) == target_stage_pram:  # if the node is the target stage
            return sum(closed_queue[best_node])
        for child in get_children(best_node, graph_pram):  # get the children of the node
            if child in closed_queue.keys():
                continue
            evaluation = [closed_queue[best_node][0] + get_edge_weight(graph_pram, best_node, child),
                          get_min_child(child, graph_pram, closed_queue)]  # get the evaluation of the node
            if child in open_queue.keys() and evaluation[0] > open_queue[child][0]:
                continue  # if the node has been visited and the evaluation is better
            open_queue[child] = evaluation  # add the node to the open queue


edge_list = ["SA", "SB", "SC", "AD", "AE", "AF", "BD", "BE", "BF", "CD", "CE", "CF", "DG", "DH", "DI", "EG", "EH", "EI",
             "FG", "FH", "FI", "GT", "HT", "IT"]  # edge list
for i in range(int(input())):
    weight_list = []
    for j in range(24):
        weight_list.append(int(input()))
    graph = dict(zip(edge_list, weight_list))  # create the graph
    target_stage = int(input())
    print(a_star(graph, target_stage))  # print the result
