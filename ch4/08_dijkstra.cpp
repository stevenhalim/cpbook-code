#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define INF 1e9

int main() {
  /*
  // Graph in Figure 4.17
  5 7 2
  2 1 2
  2 3 7
  2 0 6
  1 3 3
  1 4 6
  3 4 5
  0 4 1
  */

  freopen("08_in.txt", "r", stdin);

  int V, E, s; scanf("%d %d %d", &V, &E, &s);
  vector<vii> AL(V, vii());      // assign blank vectors of ii-s to AL
  for (int i = 0; i < E; i++) {
    int u, v, w; scanf("%d %d %d", &u, &v, &w);
    AL[u].emplace_back(v, w);                        // directed graph
  }

  // Dijkstra routine
  vi dist(V, INF); dist[s] = 0;               // INF = 1B to avoid overflow
  priority_queue<ii, vector<ii>, greater<ii>> pq; pq.push({0, s});
                        // to sort the^ pairs by increasing distance from s
  while (!pq.empty()) {                                        // main loop
    int d, u; tie(d, u) = pq.top(); pq.pop();   // get shortest unvisited u
    if (d > dist[u]) continue;            // this is a very important check
    for (auto &v : AL[u]) {                    // all outgoing edges from u
      if (dist[u]+v.second < dist[v.first]) {
        dist[v.first] = dist[u]+v.second;                // relax operation
        pq.push({dist[v.first], v.first});
  } } }     // this variant can cause duplicate items in the priority queue

  for (int i = 0; i < V; i++) // index + 1 for final answer
    printf("SSSP(%d, %d) = %d\n", s, i, dist[i]);

  return 0;
}
