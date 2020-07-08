#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { UNVISITED = -1, EXPLORED = -2, VISITED = -3 };           // three flags

// these variables have to be global to be easily accessible by our recursion (other ways exist)
vector<vii> AL;
vi dfs_num; 
vi dfs_parent;                                   // back vs bidirectional

void cycleCheck(int u) {                         // check edge properties
  dfs_num[u] = EXPLORED;                         // color u as EXPLORED
  for (auto &[v, w] : AL[u]) {                   // C++17 style, w ignored
    if (dfs_num[v] == UNVISITED) {               // EXPLORED->UNVISITED
      dfs_parent[v] = u;                         // a tree edge u->v
      cycleCheck(v);
    }
    else if (dfs_num[v] == EXPLORED) {           // EXPLORED->EXPLORED
      if (v == dfs_parent[u])                    // differentiate them
        printf(" Bidirectional Edge (%d, %d)-(%d, %d)\n", u, v, v, u);
      else // the most frequent application: check if the graph is cyclic
        printf("Back Edge (%d, %d) (Cycle)\n", u, v);
    }
    else if (dfs_num[v] == VISITED)              // EXPLORED->VISITED
      printf("  Forward/Cross Edge (%d, %d)\n", u, v);
  }
  dfs_num[u] = VISITED;                          // color u as VISITED/DONE
}

int main() {
  /*
  // Undirected Graph in Figure 4.1
  9
  1 1 0
  3 0 0 2 0 3 0
  2 1 0 3 0
  3 1 0 2 0 4 0
  1 3 0
  0
  2 7 0 8 0
  1 6 0
  1 6 0
  */

  // freopen("dfs_cc_in.txt", "r", stdin);

  /*
  // Directed graph in Figure 4.9
  8
  1 1 0
  1 3 0
  1 1 0
  2 2 0 4 0
  1 5 0
  1 7 0
  1 4 0
  1 6 0
  */

  freopen("scc_in.txt", "r", stdin);

  int V; scanf("%d", &V);
  AL.assign(V, vii());
  for (int u = 0; u < V; ++u) {
    int k; scanf("%d", &k);
    while (k--) {
      int v, w; scanf("%d %d", &v, &w);
      AL[u].emplace_back(v, w);
    }
  }

  printf("Graph Edges Property Check\n");
  dfs_num.assign(V, UNVISITED);
  dfs_parent.assign(V, -1);
  for (int u = 0; u < V; ++u)
    if (dfs_num[u] == UNVISITED)
      cycleCheck(u);

  return 0;
}
