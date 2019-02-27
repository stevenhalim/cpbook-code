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
  for (int i = 0; i < E; i++) {
    int u, v, w; scanf("%d %d %d", &u, &v, &w);
    AL[u].emplace_back(v, w);                    // directed graph
  }

  // (Modified) Dijkstra's routine
  vi dist(V, INF); dist[s] = 0;
  priority_queue<ii, vector<ii>, greater<ii>> pq; pq.push({0, s});
  // sort the pairs by increasing distance from s
  while (!pq.empty()) {                          // main loop
    // int d, u; tie(d, u) = pq.top(); pq.pop(); // C++11 style
    auto [d, u] = pq.top(); pq.pop();            // C++17 style
    if (d > dist[u]) continue;                   // a very important check
    for (auto &[v, w] : AL[u]) {                 // all edges from u
      if (dist[u]+w < dist[v]) {
        dist[v] = dist[u]+w;                     // relax operation
        pq.push({dist[v], v});
      } // this variant can cause duplicate items in the priority queue
    }
  }

  for (int i = 0; i < V; i++)
    printf("SSSP(%d, %d) = %d\n", s, i, dist[i]);

  return 0;
}
