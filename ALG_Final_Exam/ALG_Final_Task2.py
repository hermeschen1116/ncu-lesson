def initialize_path_map(size_prams):
    path_map_return = []
    for n in range(size_prams):
        tmp = []
        for j in range(size_prams):
            if n == j:
                tmp.append(0)
            else:
                tmp.append(float('inf'))
        path_map_return.append(tmp)

    return path_map_return


def add_edge(path_map_prams, start_node_prams, terminal_node_prams, weight_prams):
    path_map_prams[ord(start_node_prams) - 97][ord(terminal_node_prams) - 97] = weight_prams


def floyd_warshall(path_map_prams):
    map_size = len(path_map_prams)
    for n_1 in range(map_size):
        for n_0 in range(map_size):
            for n_2 in range(map_size):
                if path_map_prams[n_0][n_2] > path_map_prams[n_0][n_1] + path_map_prams[n_1][n_2]:
                    path_map_prams[n_0][n_2] = path_map_prams[n_0][n_1] + path_map_prams[n_1][n_2]


def print_path_map(path_map_prams):
    map_size = len(path_map_prams)
    for n_0 in range(map_size):
        for n_1 in range(map_size-1):
            if path_map_prams[n_0][n_1] == float('inf'):
                print('INF', end=' ')
            else:
                print(path_map_prams[n_0][n_1], end=' ')
        if path_map_prams[n_0][map_size-1] == float('inf'):
            print('INF')
        else:
            print(path_map_prams[n_0][map_size-1])


num_node, num_edge = map(int, input().split())
path_map = initialize_path_map(num_node)
for i in range(num_edge):
    start_node, terminal_node, weight = input().split()
    add_edge(path_map, start_node, terminal_node, int(weight))
floyd_warshall(path_map)
print_path_map(path_map)
