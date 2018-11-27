#include <bits/stdc++.h>
using namespace std;

#define MAX_V 1010

typedef pair<int, int> ii;
typedef vector<ii> vii;

int AM[MAX_V][MAX_V]; // it is better to declare large (2D) array as global

int main() {
  // Try this input for Adjacency Matrix/Adjacency List/Edge List
  // Adjacency Matrix AM
  //   for each line: |V| entries, 0 or the weight
  // Adjacency List AL
  //   for each line: num neighbors, list of neighbors + weight pairs
  // Edge List EL
  //   for each line: a-b of edge(a,b) and weight
  /*
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
  */
  freopen("07_in.txt", "r", stdin);

  int V; scanf("%d", &V);                  // we must know this size first!
                        // remember that if V is > 2000, try NOT to use AM!
  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
      scanf("%d", &AM[i][j]);

  printf("Neighbors of vertex 0:\n");
  for (int j = 0; j < V; j++)                                     // O(|V|)
    if (AM[0][j])
      printf("Edge 0-%d (weight = %d)\n", j, AM[0][j]);

  scanf("%d", &V);
  vector<vii> AL(V, vii());          // initialize AL with V entries of vii
  for (int i = 0; i < V; i++) {
    int total_neighbors; scanf("%d", &total_neighbors);
    for (int j = 0; j < total_neighbors; j++) {
      int id, weight; scanf("%d %d", &id, &weight);
      AL[i].push_back({id-1, weight});      // some index adjustment
    }
  }

  printf("Neighbors of vertex 0:\n");
  for (auto &v_w : AL[0]) {
    // AL[0] contains the required information
    int v, weight; tie(v, weight) = v_w;
    // O(k), where k is the number of neighbors
    printf("Edge 0-%d (weight = %d)\n", v, weight);
  }

  int E; scanf("%d", &E);
  priority_queue<pair<int, ii>> EL;           // one way to store Edge List
  for (int i = 0; i < E; i++) {
    int a, b, weight; scanf("%d %d %d", &a, &b, &weight);
    EL.push(make_pair(-weight, ii(a, b)));   // a way to reverse sort order
  }

  // edges sorted by weight (smallest->largest)
  for (int i = 0; i < E; i++) {
    pair<int, ii> edge = EL.top(); EL.pop();
    // negate the weight again
    printf("weight: %d (%d-%d)\n", -edge.first, edge.second.first, edge.second.second);
  }

  return 0;
}
