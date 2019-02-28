// Come and Go
// check if the graph is strongly connected, i.e. the SCC of the graph is the graph itself (only 1 SCC)

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int DFS_WHITE = -1;

int i, j, N, M, V, W, P, dfsNumberCounter, numSCC;
vector<vii> AL, ALT;
vi dfs_num, dfs_low, S, visited;                 // global variables

void tarjanSCC(int u) {
  dfs_low[u] = dfs_num[u] = ++dfsNumberCounter;  // dfs_low[u] <= dfs_num[u]
  S.push_back(u);           // stores u in a vector based on order of visitation
  visited[u] = 1;
  for (auto &[v, w] : AL[u]) {
    if (dfs_num[v] == DFS_WHITE)
      tarjanSCC(v);
    if (visited[v])                              // condition for update
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }

  if (dfs_low[u] == dfs_num[u]) {         // if this is a root (start) of an SCC
    ++numSCC;
    while (1) {
      int v = S.back(); S.pop_back(); visited[v] = 0;
      if (u == v) break;
    }
  }
}

void Kosaraju(int u, int pass) {      // pass = 1 (original), 2 (transpose)
  dfs_num[u] = 1;
  vii neighbor;
  if (pass == 1) neighbor = AL[u]; else neighbor = ALT[u];
  for (auto &v : neighbor)
    if (dfs_num[v.first] == DFS_WHITE)
      Kosaraju(v.first, pass);
  S.push_back(u);       // as in finding topological order in Section 4.2.5
}

int main() {
  while (scanf("%d %d", &N, &M), (N || M)) {
    AL.assign(N, vii());
    ALT.assign(N, vii()); // the transposed graph
    for (i = 0; i < M; ++i) {
      scanf("%d %d %d", &V, &W, &P); V--; W--;
      AL[V].push_back(ii(W, 1)); // always
      ALT[W].push_back(ii(V, 1));
      if (P == 2) { // if this is two way, add the reverse direction
        AL[W].push_back(ii(V, 1));
        ALT[V].push_back(ii(W, 1));
      }
    }

    //// run Tarjan's SCC code here
    //dfs_num.assign(N, DFS_WHITE); dfs_low.assign(N, 0); visited.assign(N, 0);
    //dfsNumberCounter = numSCC = 0;
    //for (i = 0; i < N; ++i)
    //  if (dfs_num[i] == DFS_WHITE)
    //    tarjanSCC(i);

    // run Kosaraju's SCC code here
    S.clear();  // first pass is to record the `post-order' of original graph
    dfs_num.assign(N, DFS_WHITE);
    for (i = 0; i < N; ++i)
      if (dfs_num[i] == DFS_WHITE)
        Kosaraju(i, 1);
    numSCC = 0;   // second pass: explore the SCCs based on first pass result
    dfs_num.assign(N, DFS_WHITE);
    for (i = N-1; i >= 0; --i)
      if (dfs_num[S[i]] == DFS_WHITE)
        ++numSCC, Kosaraju(S[i], 2);    // on the transpose of original graph
    // if SCC is only 1, print 1, otherwise, print 0
    printf("%d\n", numSCC == 1 ? 1 : 0);
  }
  return 0;
}
