from collections import defaultdict
import heapq 

def main():
    # Try this input for Adjacency Matrix/Adjacency List/Edge List
    # Adjacency Matrix AM
    #    for each line: |V| entries, 0 or the weight
    #  Adjacency List AL
    #    for each line: num neighbors, list of neighbors + weight pairs
    #  Edge List EL
    #    for each line: a-b of edge(a,b) and weight
    '''
      6
        0  10   0   0 100   0
      10   0   7   0   8   0
        0   7   0   9   0   0
        0   0   9   0  20   5
      100   8   0  20   0   0
        0   0   0   5   0   0
      6
      2 2 10 5 100
      3 1 10 3 7 5 8
      2 2 7 4 9
      3 3 9 5 20 6 5
      3 1 100 2 8 4 20
      1 4 5
      7
      1 2 10
      1 5 100
      2 3 7
      2 5 8
      3 4 9
      4 5 20
      4 6 5
    '''
    fh = open("graph_ds.txt", "r")
    V = int(fh.readline()) # we must know this size first!
    # remember that if V is > 2000, try NOT to use AM!

    #adjacency matrix
    AM = [[0 for i in range(V)] for j in range(V)]
    for i in range(V):
        AM[i] = list(map(int, (fh.readline().strip().split())))

    print("Neighbors of vertex 0:");
    for j in range(V):                             # O(|V|)
        if AM[0][j]:
            print('Edge 0-{:d} (weight = {:d})'.format(j, AM[0][j]))

    V = int(fh.readline())

    AL = defaultdict(list) #initalize AL
    for i in range(V):
        line = list(map(int, (fh.readline().strip().split())))
        total_neighbours = int(line[0])
        for j in range(1, len(line), 2):
            v, w = int(line[j]), int(line[j + 1])
            AL[i].append((v - 1, w))

    print("Neighbors of vertex 0:");
    for v_w in AL[0]:                            
    # AL[0] contains the required information 
        print('Edge 0-{:d} (weight = {:d})'.format(v_w[0], v_w[1]))  

    E = int(fh.readline())
    edge_list = []
    for i in range(E):
        u, v, w = map(int, fh.readline().split())
        edge_list.append((w, u, v))

    # build a heap
    heapq.heapify(edge_list)

    # edges sorted by weight (smallest->largest)
    for i in range(E):
        edge = heapq.heappop(edge_list)
        print('weight: {:d} ({:d}-{:d})'.format(edge[0], edge[1], edge[2]));

main()
