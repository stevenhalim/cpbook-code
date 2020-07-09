// Come and Go
// check if the graph is strongly connected, i.e. the SCC of the graph is the graph itself (only 1 SCC)

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

enum { UNVISITED = -1 };

int dfsNumberCounter, numSCC;
vector<vii> AL, AL_T;
vi dfs_num, dfs_low, S, visited;                 // global variables
stack<int> St;

void tarjanSCC(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter;    // dfs_low[u]<=dfs_num[u]
  dfsNumberCounter++;                            // increase counter
  St.push(u);                                    // remember the order
  visited[u] = 1;
  for (auto &[v, w] : AL[u]) {
    if (dfs_num[v] == UNVISITED)
      tarjanSCC(v);
    if (visited[v])                              // condition for update
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }

  if (dfs_low[u] == dfs_num[u]) {                // a root/start of an SCC
    ++numSCC;                                    // when recursion unwinds
    while (1) {
      int v = St.top(); St.pop(); visited[v] = 0;
      if (u == v) break;
    }
  }
}

void Kosaraju(int u, int pass) { // pass = 1 (original), 2 (transpose)
  dfs_num[u] = 1;
  vii &neighbor = (pass == 1) ? AL[u] : AL_T[u]; // by ref to avoid copying
  for (auto &[v, w] : neighbor)                  // C++17 style, w ignored
    if (dfs_num[v] == UNVISITED)
      Kosaraju(v, pass);
  S.push_back(u); // as in finding topological order in Section 4.2.5
}

int main() {
  int N, M;
  while (scanf("%d %d", &N, &M), (N || M)) {
    AL.assign(N, vii());
    AL_T.assign(N, vii()); // the transposed graph
    while (M--) {
      int V, W, P; scanf("%d %d %d", &V, &W, &P); --V; --W; // to 0-based indexing
      AL[V].emplace_back(W, 1); // always
      AL_T[W].emplace_back(V, 1);
      if (P == 2) { // if this is two way, add the reverse direction
        AL[W].emplace_back(V, 1);
        AL_T[V].emplace_back(W, 1);
      }
    }

    // run Tarjan's SCC code here
    dfs_num.assign(N, UNVISITED); dfs_low.assign(N, 0); visited.assign(N, 0);
    while (!St.empty()) St.pop();
    dfsNumberCounter = numSCC = 0;
    for (int u = 0; u < N; ++u)
     if (dfs_num[u] == UNVISITED)
       tarjanSCC(u);

    // // run Kosaraju's SCC code here
    // S.clear(); // first pass: record the post-order of original graph
    // dfs_num.assign(N, UNVISITED);
    // for (int u = 0; u < N; ++u)
    //   if (dfs_num[u] == UNVISITED)
    //     Kosaraju(u, 1);
    // int numSCC = 0; // second pass: explore SCCs using first pass order
    // dfs_num.assign(N, UNVISITED);
    // for (int i = N-1; i >= 0; --i)
    //   if (dfs_num[S[i]] == UNVISITED)
    //     numSCC++, Kosaraju(S[i], 2);             // on transposed graph

    // if SCC is only 1, print 1, otherwise, print 0
    printf("%d\n", numSCC == 1 ? 1 : 0);
  }
  return 0;
}
