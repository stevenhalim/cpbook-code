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
  // Graph in Figure 4.18, has negative weight, but no negative cycle
  5 5 0
  0 1 1
  0 2 10
  1 3 2
  2 3 -10
  3 4 3

  // Graph in Figure 4.19, negative cycle exists
  3 3 0
  0 1 1000
  1 2 15
  2 1 -42
  */

  freopen("bellman_ford_in.txt", "r", stdin);

  int V, E, s; scanf("%d %d %d", &V, &E, &s);
  vector<vii> AL(V, vii());
  for (int i = 0; i < E; ++i) {
    int u, v, w; scanf("%d %d %d", &u, &v, &w);
    AL[u].emplace_back(v, w);
  }

  // Bellman Ford's routine, basically = relax all E edges V-1 times
  vi dist(V, INF); dist[s] = 0;
  for (int i = 0; i < V-1; ++i)                  // total O(V*E)
    for (int u = 0; u < V; ++u)                  // these two loops = O(E)
      if (dist[u] != INF)                        // important check
        for (auto &[v, w] : AL[u])               // C++17 style
          dist[v] = min(dist[v], dist[u]+w);

  bool hasNegativeCycle = false;
  for (int u = 0; u < V; ++u)                    // one more pass to check
    if (dist[u] != INF)
      for (auto &[v, w] : AL[u])                 // C++17 style
        if (dist[v] > dist[u]+w)                 // should be false
          hasNegativeCycle = true;               // if true => -ve cycle
  printf("Negative Cycle Exist? %s\n", hasNegativeCycle ? "Yes" : "No");

  if (!hasNegativeCycle)
    for (int i = 0; i < V; ++i)
      printf("SSSP(%d, %d) = %d\n", s, i, dist[i]);

  return 0;
}
