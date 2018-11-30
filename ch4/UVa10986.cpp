// Sending email
// standard SSSP problem
// demo using Dijkstra's and SPFA

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define INF 1e9

int i, j, TC, V, E, s, t, a, b, w, caseNo = 1;
vector<vii> AdjList;

int main() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
#endif

  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d %d %d", &V, &E, &s, &t);

    // build graph
    AdjList.assign(V, vii());
    while (E--) {
      scanf("%d %d %d", &a, &b, &w);
      AdjList[a].push_back(ii(b, w)); // bidirectional
      AdjList[b].push_back(ii(a, w));
    }

/*
    // Dijkstra from source s
    vi dist(V, INF); dist[s] = 0;
    priority_queue< ii, vii, greater<ii> > pq; pq.push(ii(0, s)); // sort based on increasing distance

    while (!pq.empty()) { // main loop
      ii top = pq.top(); pq.pop(); // greedy: pick shortest unvisited vertex
      int d = top.first, u = top.second;
      if (d != dist[u]) continue;
      for (auto v : AdjList[u]) // all outgoing edges from u
        if (dist[u] + v.second < dist[v.first]) { // if can relax
          dist[v.first] = dist[u] + v.second; // relax
          pq.push(ii(dist[v.first], v.first)); // enqueue this neighbor
        }                          // regardless it is already in pq or not
    }
*/

    // SPFA from source S
    // initially, only source vertex s has dist[s] = 0 and in the queue
    vi dist(V, INF); dist[s] = 0;
    queue<int> q; q.push(s);
    vi in_queue(V, 0); in_queue[s] = 1;
    while (!q.empty()) {
      int u = q.front(); q.pop(); in_queue[u] = 0;          // pop from queue
      for (auto &v : AdjList[u])                 // all outgoing edges from u
        if (dist[u]+v.second < dist[v.first]) {               // if can relax
          dist[v.first] = dist[u]+v.second;                          // relax
          if (!in_queue[v.first]) {                       // add to the queue
            q.push(v.first);                 // only if it's not in the queue
            in_queue[v.first] = 1;
    }   } }

    printf("Case #%d: ", caseNo++);
    if (dist[t] != INF) printf("%d\n", dist[t]);
    else                printf("unreachable\n");
  }

  return 0;
}
