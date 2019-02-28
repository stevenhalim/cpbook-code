// February 2019 note:
// This code uses new C++17 structured binding
// use this compiler setting "g++ -O2 -std=gnu++17 {cpp17file}"

// note to self: for CP4, make the O(VE^2) default or change to dinic

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int INF = 1e9; // INF = 1B, not 2^31-1 to avoid overflow
const int MAX_V = 100; // enough for sample graph in Figure 4.24/4.25/4.26/UVa 00259

int V, k, vertex, weight;
int res[MAX_V][MAX_V], mf, f, s, t;              // global variables
vector<vii> AL; // res and AL contain the same flow graph
vi p;

void augment(int v, int minEdge) {               // traverse BFS from s->t
  if (v == s) { f = minEdge; return; }           // record minEdge
  else if (p[v] != -1) {
    augment(p[v], min(minEdge, res[p[v]][v]));
    res[p[v]][v] -= f; res[v][p[v]] += f;        // update residual weights
  }
}

int main() {
  /*
  // Graph in Figure 4.24
  4 0 1
  2 2 70 3 30
  2 2 25 3 70
  3 0 70 3 5 1 25
  3 0 30 2 5 1 70

  // Graph in Figure 4.25
  4 0 3
  2 1 100 2 100
  2 2 1 3 100
  1 3 100
  0

  // Graph in Figure 4.26.A
  5 0 1
  2 2 100 3 50
  0
  3 3 50 4 50 1 50
  1 4 100
  1 1 125

  // Graph in Figure 4.26.B
  5 0 1
  2 2 100 3 50
  0
  3 3 50 4 50 1 50
  1 4 100
  1 1 75

  // Graph in Figure 4.26.C
  5 0 1
  2 2 100 3 50
  0
  2 4 5 1 5
  1 4 100
  1 1 125
  */

  freopen("maxflow_in.txt", "r", stdin);

  scanf("%d %d %d", &V, &s, &t);
  memset(res, 0, sizeof res);
  AL.assign(V, vii());
  for (int u = 0; u < V; ++u) {
    int k; scanf("%d", &k);
    while (k--) {
      int v, w; scanf("%d %d", &v, &w);
      res[u][v] = w;
      AL[u].emplace_back(v, 1);                  // to record structure
      AL[v].emplace_back(u, 1);                  // remember the back edge
    }
  }

  mf = 0;                                        // mf stands for max_flow
  while (1) {                                    // an O(VE^2) EK algorithm
    f = 0;
    // run BFS, compare with the original BFS shown in Section 4.2.2
    bitset<MAX_V> vis; vis[s] = true;            // now using bitset
    queue<int> q; q.push(s);
    p.assign(MAX_V, -1);                         // record BFS sp tree
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == t) break; // immediately stop BFS if we already reach sink t
      for (auto &[v, w] : AL[u])                 // C++17 style
        if (res[u][v] > 0 && !vis[v])
          vis[v] = true, q.push(v), p[v] = u;    // 3 lines in one!
    }
    augment(t, INF);                             // find bottleneck weight
    if (f == 0) break;                           // if flow == 0, stop
    mf += f;                                     // if flow > 0, add to mf
  }
  printf("%d\n", mf);                            // the max flow value

  // To-do: Implement Dinic's here

  // To-do: Implement Push-Relabel here?

  return 0;
}
