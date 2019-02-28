// Sending email
// standard SSSP problem
// demo using Dijkstra's and SPFA

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const int INF = 1e9;

int main() {
  int TC; scanf("%d", &TC);
  int caseNo = 1;
  while (TC--) {
    int V, E, s, t; scanf("%d %d %d %d", &V, &E, &s, &t);
    vector<vii> AL(V, vii()); // build graph
    while (E--) {
      int a, b, w; scanf("%d %d %d", &a, &b, &w);
      AL[a].emplace_back(b, w); // bidirectional
      AL[b].emplace_back(a, w);
    }
/*
    // Dijkstra from source s
    vi dist(V, INF); dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq; pq.push(ii(0, s)); // sort based on increasing distance

    while (!pq.empty()) { // main loop
      ii top = pq.top(); pq.pop();               // greedy: pick shortest unvisited vertex
      int d = top.first, u = top.second;
      if (d != dist[u]) continue;
      for (auto &[v, w] : AL[u])                 // all outgoing edges from u
        if (dist[u]+w < dist[v]) {               // if can relax
          dist[v] = dist[u]+w;                   // relax
          pq.push({dist[v], v});                 // enqueue this neighbor
        }                                        // regardless it is already in pq or not
    }
*/
    // SPFA from source S
    // initially, only source vertex s has dist[s] = 0 and in the queue
    vi dist(V, INF); dist[s] = 0;
    queue<int> q; q.push(s);
    vi in_queue(V, 0); in_queue[s] = 1;
    while (!q.empty()) {
      int u = q.front(); q.pop(); in_queue[u] = 0; // pop from queue
      for (auto &[v, w] : AL[u])                 // all outgoing edges from u
        if (dist[u]+w < dist[v]) {               // if can relax
          dist[v] = dist[u]+w;                   // relax
          if (!in_queue[v]) {                    // add to the queue
            q.push(v);                           // only if it's not in the queue
            in_queue[v] = 1;
          }
        }
    }
    printf("Case #%d: ", ++caseNo);
    if (dist[t] != INF) printf("%d\n", dist[t]);
    else                printf("unreachable\n");
  }
  return 0;
}
