// February 2019 note:
// This code uses new C++17 structured binding
// use this compiler setting "g++ -O2 -std=gnu++17 {cpp17file}"

#include <bits/stdc++.h>
using namespace std;

// In this chapter, we will frequently use these three data type shortcuts
// They may look cryptic but shortcuts are useful in competitive programming
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const int DFS_WHITE = -1; // normal DFS, do not change this with other values (other than 0), because we usually use memset with conjunction with DFS_WHITE
const int DFS_BLACK = 1;

vector<vii> AL;

void printThis(string message) {
  printf("==================================\n");
  printf("%s\n", message.c_str());
  printf("==================================\n");
}

vi dfs_num; // this variable has to be global, we cannot put it in recursion
int numCC;

void dfs(int u) { // DFS for normal usage: as graph traversal algorithm
  printf(" %d", u);                              // this vertex is visited
  dfs_num[u] = DFS_BLACK;                        // mark u as visited
  for (auto &[v, w] : AL[u])                     // (neighbor, weight) pair
    if (dfs_num[v] == DFS_WHITE)                 // to avoid cycle
      dfs(v);                                    // recursively visits v
} // for simple graph traversal, we ignore the weight

// note: this is not the version on implicit graph
void floodfill(int u, int color) {
  dfs_num[u] = color;                            // not just a generic DFS_BLACK
  for (auto &[v, w] : AL[u])
    if (dfs_num[v] == DFS_WHITE)
      floodfill(v, color);
}

vi topoSort; // global vector to store the toposort in reverse order

void dfs2(int u) { // change function name to differentiate with original dfs
  dfs_num[u] = DFS_BLACK;
  for (auto &[v, w] : AL[u])
    if (dfs_num[v] == DFS_WHITE)
      dfs2(v);
  topoSort.push_back(u);                         // this is the only change
}

#define DFS_GRAY 2                               // one more color
vi dfs_parent; // to differentiate real back edge versus bidirectional edge

void graphCheck(int u) { // DFS for checking graph edge properties
  dfs_num[u] = DFS_GRAY; // color this as DFS_GRAY (temp) instead of DFS_BLACK
  for (auto &[v, w] : AL[u]) {
    if (dfs_num[v] == DFS_WHITE) {               // Tree Edge
      dfs_parent[v] = u;                         // parent of v is me (u)
      graphCheck(v);
    }
    else if (dfs_num[v] == DFS_GRAY) {           // DFS_GRAY to DFS_GRAY
      if (v == dfs_parent[u])                    // to differentiate
        printf(" Bidirectional (%d, %d) - (%d, %d)\n", u, v, v, u);
      else  // the most frequent application: check if the given graph is cyclic
        printf(" Back Edge (%d, %d) (Cycle)\n", u, v);
    }
    else if (dfs_num[v] == DFS_BLACK)            // DFS_GRAY to DFS_BLACK
      printf(" Forward/Cross Edge (%d, %d)\n", u, v);
  }
  dfs_num[u] = DFS_BLACK; // after recursion, color this as DFS_BLACK (DONE)
}

vi dfs_low; // additional information for articulation points/bridges/SCCs
vi articulation_vertex;
int dfsNumberCounter, dfsRoot, rootChildren;

void articulationPointAndBridge(int u) {
  dfs_low[u] = dfs_num[u] = ++dfsNumberCounter;  // dfs_low[u] <= dfs_num[u]
  for (auto &[v, w] : AL[u]) {
    if (dfs_num[v] == DFS_WHITE) {               // a tree edge
      dfs_parent[v] = u;
      if (u == dfsRoot) ++rootChildren;          // special case, root

      articulationPointAndBridge(v);

      if (dfs_low[v] >= dfs_num[u])              // for articulation point
        articulation_vertex[u] = true;           // store this info first
      if (dfs_low[v] > dfs_num[u])               // for bridge
        printf(" Edge (%d, %d) is a bridge\n", u, v);
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);  // update dfs_low[u]
    }
    else if (v != dfs_parent[u])                 // a back edge, not direct cycle
      dfs_low[u] = min(dfs_low[u], dfs_num[v]);  // update dfs_low[u]
  }
}

vi S, visited;                                   // additional global variables
int numSCC;

void tarjanSCC(int u) {
  dfs_low[u] = dfs_num[u] = ++dfsNumberCounter;  // dfs_low[u] <= dfs_num[u]
  S.push_back(u); // stores u in a vector based on order of visitation
  visited[u] = 1;
  for (auto &[v, w] : AL[u]) {
    if (dfs_num[v] == DFS_WHITE)
      tarjanSCC(v);
    if (visited[v])                              // condition for update
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }

  if (dfs_low[u] == dfs_num[u]) {                // a root/start of an SCC
    printf("SCC %d:", ++numSCC);                 // when recursion unwinds
    while (1) {
      int v = S.back(); S.pop_back(); visited[v] = 0;
      printf(" %d", v);
      if (u == v) break;
    }
    printf("\n");
  }
}

int main() {
  /*
  // Use the following input:
  // Graph in Figure 4.1
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

  // Example of directed acyclic graph in Figure 4.4 (for toposort)
  8
  2 1 0 2 0
  2 2 0 3 0
  2 3 0 5 0
  1 4 0
  0
  0
  0
  1 6 0

  // Example of directed graph with back edges
  3
  1 1 0
  1 2 0
  1 0 0

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

  freopen("dfs_in.txt", "r", stdin);

  int V; scanf("%d", &V);
  AL.assign(V, vii()); // assign blank vectors of pair<int, int>s to Al
  for (int u = 0; u < V; ++u) {
    int total_neighbors; scanf("%d", &total_neighbors);
    for (int j = 0; j < total_neighbors; ++j) {
      int v, w; scanf("%d %d", &v, &w);
      AL[u].emplace_back(v, w);
    }
  }

  printThis("Standard DFS Demo (the input graph must be UNDIRECTED)");
  numCC = 0;
  dfs_num.assign(V, DFS_WHITE);
  for (int u = 0; u < V; ++u)                    // for each u in [0..V-1]
    if (dfs_num[u] == DFS_WHITE)                 // if that u is unvisited
      printf("CC %d:", ++numCC), dfs(u), printf("\n"); // 3 lines here!
  printf("There are %d connected components\n", numCC);

  printThis("Flood Fill Demo (the input graph must be UNDIRECTED)");
  numCC = 0;
  dfs_num.assign(V, DFS_WHITE);
  for (int u = 0; u < V; ++u)
    if (dfs_num[u] == DFS_WHITE)
      floodfill(u, ++numCC);
  for (int u = 0; u < V; ++u)
    printf("Vertex %d has color %d\n", u, dfs_num[u]);

  // make sure that the given graph is DAG
  printThis("Topological Sort (the input graph must be DAG)");
  topoSort.clear();
  dfs_num.assign(V, DFS_WHITE);
  for (int u = 0; u < V; ++u)                    // same as finding CCs
    if (dfs_num[u] == DFS_WHITE)
      dfs2(u);
  reverse(topoSort.begin(), topoSort.end());     // reverse topoSort or
  for (auto &u : topoSort)                       // simply read the content
    printf(" %d", u);                            // of `topoSort' backwards
  printf("\n");

  printThis("Graph Edges Property Check");
  numCC = 0;
  dfs_num.assign(V, DFS_WHITE); dfs_parent.assign(V, -1);
  for (int u = 0; u < V; ++u)
    if (dfs_num[u] == DFS_WHITE)
      printf("Component %d:\n", ++numCC), graphCheck(u); // 2 lines in one

  printThis("Articulation Points & Bridges (the input graph must be UNDIRECTED)");
  dfsNumberCounter = 0; dfs_num.assign(V, DFS_WHITE); dfs_low.assign(V, 0);
  dfs_parent.assign(V, -1); articulation_vertex.assign(V, 0);
  printf("Bridges:\n");
  for (int u = 0; u < V; ++u)
    if (dfs_num[u] == DFS_WHITE) {
      dfsRoot = u; rootChildren = 0;
      articulationPointAndBridge(u);
      articulation_vertex[dfsRoot] = (rootChildren > 1); // special case
    }
  printf("Articulation Points:\n");
  for (int u = 0; u < V; ++u)
    if (articulation_vertex[u])
      printf(" Vertex %d\n", u);

  printThis("Strongly Connected Components (the input graph must be DIRECTED)");
  dfs_num.assign(V, DFS_WHITE); dfs_low.assign(V, 0); visited.assign(V, 0);
  dfsNumberCounter = numSCC = 0;
  for (int u = 0; u < V; ++u)
    if (dfs_num[u] == DFS_WHITE)
      tarjanSCC(u);

  return 0;
}
