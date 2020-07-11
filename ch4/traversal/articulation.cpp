#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { UNVISITED = -1 };                              // basic flag

// these variables have to be global to be easily accessible by our recursion (other ways exist)
vector<vii> AL;
vi dfs_num, dfs_low, dfs_parent, articulation_vertex;
int dfsNumberCounter, dfsRoot, rootChildren;

void articulationPointAndBridge(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++;  // dfs_low[u]<=dfs_num[u]
  for (auto &[v, w] : AL[u]) {
    if (dfs_num[v] == UNVISITED) {               // a tree edge
      dfs_parent[v] = u;
      if (u == dfsRoot) ++rootChildren;          // special case, root

      articulationPointAndBridge(v);

      if (dfs_low[v] >= dfs_num[u])              // for articulation point
        articulation_vertex[u] = 1;              // store this info first
      if (dfs_low[v] > dfs_num[u])               // for bridge
        printf(" Edge (%d, %d) is a bridge\n", u, v);
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);  // subtree, always update
    }
    else if (v != dfs_parent[u])                 // if a non-trivial cycle
      dfs_low[u] = min(dfs_low[u], dfs_num[v]);  // then can update
  }
}

int main() {
  /*
  // Left graph in Figure 4.6/4.7/4.8
  6
  1 1 0
  3 0 0 2 0 4 0
  1 1 0
  1 4 0
  3 1 0 3 0 5 0
  1 4 0

  // Right graph in Figure 4.6/4.7/4.8
  6
  1 1 0
  5 0 0 2 0 3 0 4 0 5 0
  1 1 0
  1 1 0
  2 1 0 5 0
  2 1 0 4 0
  */

  freopen("articulation_in.txt", "r", stdin);

  int V; scanf("%d", &V);
  AL.assign(V, vii());
  for (int u = 0; u < V; ++u) {
    int k; scanf("%d", &k);
    while (k--) {
      int v, w; scanf("%d %d", &v, &w);
      AL[u].emplace_back(v, w);
    }
  }

  printf("Articulation Points & Bridges (the input graph must be UNDIRECTED)\n");
  dfs_num.assign(V, UNVISITED); dfs_low.assign(V, 0);
  dfs_parent.assign(V, -1); articulation_vertex.assign(V, 0);
  dfsNumberCounter = 0;
  printf("Bridges:\n");
  for (int u = 0; u < V; ++u)
    if (dfs_num[u] == UNVISITED) {
      dfsRoot = u; rootChildren = 0;
      articulationPointAndBridge(u);
      articulation_vertex[dfsRoot] = (rootChildren > 1); // special case
    }

  printf("Articulation Points:\n");
  for (int u = 0; u < V; ++u)
    if (articulation_vertex[u])
      printf(" Vertex %d\n", u);

  return 0;
}
