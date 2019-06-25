// February 2019 note:
// This code uses new C++17 structured binding
// use this compiler setting "g++ -O2 -std=gnu++17 {cpp17file}"

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int INF = 1e9; // INF = 1B, not 2^31-1 to avoid overflow

int main() {
  /*
  // Graph in Figure 4.17
  5 7 0
  0 1 2
  0 2 6
  0 3 7
  1 3 3
  1 4 6
  2 4 1
  3 4 5
  */

  freopen("dijkstra_in.txt", "r", stdin);

  int V, E, s; scanf("%d %d %d", &V, &E, &s);
  vector<vii> AL(V, vii());
  for (int i = 0; i < E; ++i) {
    int u, v, w; scanf("%d %d %d", &u, &v, &w);
    AL[u].emplace_back(v, w);                    // directed graph
  }

  // (Modified) Dijkstra's routine
  vi dist(V, INF); dist[s] = 0;
  priority_queue<ii, vector<ii>, greater<ii>> pq; pq.push({0, s});
  // sort the pairs by increasing distance from s
  while (!pq.empty()) {                          // main loop
    auto [d, u] = pq.top(); pq.pop();            // shortest unvisited u
    if (d > dist[u]) continue;                   // a very important check
    for (auto &[v, w] : AL[u]) {                 // all edges from u
      if (dist[u]+w >= dist[v]) continue;        // not improving, skip
      dist[v] = dist[u]+w;                       // relax operation
      pq.push({dist[v], v});                     // enqueue better pair
    }
  }

  for (int u = 0; u < V; ++u)
    printf("SSSP(%d, %d) = %d\n", s, u, dist[u]);

  return 0;
}
