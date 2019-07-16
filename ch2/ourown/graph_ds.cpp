#include <bits/stdc++.h>
using namespace std;

const int MAX_V = 1010;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int> iii;

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
  freopen("graph_ds.txt", "r", stdin);

  int V; scanf("%d", &V);                        // need to know V first
  for (int u = 0; u < V; ++u)                    // if V is > 2000,
    for (int v = 0; v < V; ++v)                  // try NOT to use AM
      scanf("%d", &AM[u][v]);

  printf("Neighbors of vertex 0:\n");
  for (int v = 0; v < V; ++v)                    // O(V)
    if (AM[0][v])
      printf("Edge 0-%d (weight = %d)\n", v, AM[0][v]);

  scanf("%d", &V);
  vector<vii> AL(V, vii());                      // initialize AL
  for (int u = 0; u < V; ++u) {
    int total_neighbors; scanf("%d", &total_neighbors);
    while (total_neighbors--) {
      int v, w; scanf("%d %d", &v, &w); --v;     // to 0-based indexing
      AL[u].emplace_back(v, w);
    }
  }

  printf("Neighbors of vertex 0:\n");            // k = |neighbors|
  for (auto &[v, w] : AL[0])                     // O(k)
    printf("Edge 0-%d (weight = %d)\n", v, w);

  int E; scanf("%d", &E);
  vector<iii> EL(E);                              // one way to store EL
  for (int i = 0; i < E; ++i) {
    int u, v, w; scanf("%d %d %d", &u, &v, &w);
    EL[i] = tie(w, u, v);
  }
  // edges sorted by weight (smallest->largest)
  sort(EL.begin(), EL.end());
  for (auto &[w, u, v] : EL)                     // C++17 style
    printf("weight: %d (%d-%d)\n", w, u, v);

  return 0;
}
