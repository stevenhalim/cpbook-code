#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // INF = 1B, not 2^31-1 to avoid overflow
const int MAX_V = 450; // if |V| > 450, you cannot use Floyd Washall's

int AM[MAX_V][MAX_V]; // it is better to store a big array in the heap

int main() {
  /*
  // Graph in Figure 4.30
  5 9
  0 1 2
  0 2 1
  0 4 3
  1 3 4
  2 1 1
  2 4 1
  3 0 1
  3 2 3
  3 4 5
  */

  freopen("floyd_warshall_in.txt", "r", stdin);

  int V, E; scanf("%d %d", &V, &E);
  for (int u = 0; u < V; ++u) {
    for (int v = 0; v < V; ++v)
      AM[u][v] = INF;
    AM[u][u] = 0;
  }

  for (int i = 0; i < E; ++i) {
    int u, v, w; scanf("%d %d %d", &u, &v, &w);
    AM[u][v] = w;                                // directed graph
  }

  for (int k = 0; k < V; ++k)                    // loop order is k->u->v
    for (int u = 0; u < V; ++u)
      for (int v = 0; v < V; ++v)
        AM[u][v] = min(AM[u][v], AM[u][k]+AM[k][v]);

  for (int u = 0; u < V; ++u)
    for (int v = 0; v < V; ++v)
      printf("APSP(%d, %d) = %d\n", u, v, AM[u][v]);

  return 0;
}
