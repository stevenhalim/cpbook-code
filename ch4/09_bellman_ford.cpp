#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define INF 1e9

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

  freopen("09_in.txt", "r", stdin);

  int V, E, s; scanf("%d %d %d", &V, &E, &s);
  vector<vii> AL(V, vii());           // assign blank vectors of ii-s to AL
  for (int i = 0; i < E; i++) {
    int a, b, w; scanf("%d %d %d", &a, &b, &w);
    AL[a].emplace_back(b, w);
  }

  // Bellman Ford routine
  vi dist(V, INF); dist[s] = 0;
  for (int i = 0; i < V-1; i++) // relax all E edges V-1 times, total O(VE)
    for (int u = 0; u < V; u++)                   // these two loops = O(E)
      if (dist[u] != INF)  // important: do not propagate if dist[u] == INF
        for (auto &v : AL[u])   // we can record SP spanning here if needed
          dist[v.first] = min(dist[v.first], dist[u]+v.second);    // relax

  bool hasNegativeCycle = false;
  for (int u = 0; u < V; u++) if (dist[u] != INF) // one more pass to check
    for (auto &v : AL[u])
      if (dist[v.first] > dist[u]+v.second)            // should be false
        hasNegativeCycle = true;  // if true, then negative cycle exists!
  printf("Negative Cycle Exist? %s\n", hasNegativeCycle ? "Yes" : "No");

  if (!hasNegativeCycle)
    for (int i = 0; i < V; i++)
      printf("SSSP(%d, %d) = %d\n", s, i, dist[i]);

  return 0;
}
