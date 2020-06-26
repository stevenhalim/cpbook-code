#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int INF = 1e9; // INF = 1B, not 2^31-1 to avoid overflow

int main() {
  /*
  // Graph in Figure 4.18, has negative weight, but no negative cycle
  5 5 0
  0 1 1
  0 2 10
  1 3 2
  2 3 -10
  3 4 3

  // Graph in Figure 4.19, negative cycle exists, SPFA will be trapped in an infinite loop/produces WA (stop only when overflow happens)
  6 6 0
  0 1 99
  0 5 -99
  1 2 15
  2 3 0
  3 1 -42
  3 4 2
  */

  freopen("bellman_ford_in.txt", "r", stdin);

  int V, E, s; scanf("%d %d %d", &V, &E, &s);
  vector<vii> AL(V, vii());
  while (E--) {
    int u, v, w; scanf("%d %d %d", &u, &v, &w);
    AL[u].emplace_back(v, w);
  }

  // SPFA from source S
  vi dist(V, INF); dist[s] = 0;                  // INF = 1e9 here
  queue<int> q; q.push(s);                       // like BFS queue
  vi in_queue(V, 0); in_queue[s] = 1;            // unique to SPFA
  while (!q.empty()) {
    int u = q.front(); q.pop(); in_queue[u] = 0; // pop from queue
    for (auto &[v, w] : AL[u]) {                 // C++17 style
      if (dist[u]+w >= dist[v]) continue;        // not improving, skip
      dist[v] = dist[u]+w;                       // relax operation
      if (!in_queue[v]) {                        // add to the queue
        q.push(v);                               // only if v is not
        in_queue[v] = 1;                         // already in the queue
      }
    }
  }

  for (int u = 0; u < V; ++u)
    printf("SSSP(%d, %d) = %d\n", s, u, dist[u]);

  return 0;
}
