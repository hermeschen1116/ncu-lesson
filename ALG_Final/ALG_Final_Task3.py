def get_weight(edge_1_pram, edge_2_pram):
    return abs(edge_1_pram[0] - edge_2_pram[0]) + abs(edge_1_pram[1] - edge_2_pram[1])


def prim_span(edges_pram):
    cost_return = 0
    path = []
    size = len(edges_pram)

    min_edge = float('inf')
    for e_1 in range(size):
        for e_2 in range(size):
            if get_weight(edges_pram[e_1], edges_pram[e_2]) < min_edge and edges_pram[e_1] != edges_pram[e_2]:
                min_edge = get_weight(edges_pram[e_1], edges_pram[e_2])
                path = [edges_pram[e_1], edges_pram[e_2]]
    cost_return += min_edge

    while len(path) != len(edges_pram):
        min_edge = float('inf')
        min_index = 0
        if len(path) == 0:
            for e_1 in range(size):
                for e_2 in range(size):
                    if get_weight(edges_pram[e_1], edges_pram[e_2]) < min_edge and edges_pram[e_1] != edges_pram[e_2]:
                        min_edge = get_weight(edges_pram[e_1], edges_pram[e_2])
                        path = [edges_pram[e_1], edges_pram[e_2]]
        else:
            for e_1 in range(len(path)):
                for e_2 in range(size):
                    if get_weight(path[e_1], edges_pram[e_2]) < min_edge and edges_pram[e_2] not in path:
                        min_edge = get_weight(path[e_1], edges_pram[e_2])
                        min_index = e_2
            path.append(edges_pram[min_index])
        cost_return += min_edge

    return cost_return


for i in range(int(input())):
    edges = []
    for j in range(int(input())):
        edges.append(list(map(int, input().split())))
    print(prim_span(edges))
