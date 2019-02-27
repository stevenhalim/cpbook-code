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
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++)
      AM[i][j] = INF;
    AM[i][i] = 0;
  }

  for (int i = 0; i < E; i++) {
    int u, v, w; scanf("%d %d %d", &u, &v, &w);
    AM[u][v] = w;                                // directed graph
  }

  for (int k = 0; k < V; k++)                    // loop order is k->i->j
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++)
        AM[i][j] = min(AM[i][j], AM[i][k]+AM[k][j]);

  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
      printf("APSP(%d, %d) = %d\n", i, j, AM[i][j]);

  return 0;
}
