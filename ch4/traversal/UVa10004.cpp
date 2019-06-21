// Bicoloring

#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

typedef vector<int> vi;

int main() {
  int n;
  while (scanf("%d", &n), n) {
    vector<vi> AL(n, vi());
    int l; scanf("%d", &l);
    while (l--) {
      int a, b; scanf("%d %d", &a, &b);
      AL[a].push_back(b);
      AL[b].push_back(a); // bidirectional
    }
    int s = 0;
    queue<int> q; q.push(s);
    vi color(n, INF); color[s] = 0;
    bool isBipartite = true;   // add one more boolean flag, initially true
    while (!q.empty() && isBipartite) { // as with the original BFS routine
      int u = q.front(); q.pop();
      for (auto &v : AL[u]) {
        if (color[v] == INF) {       // but, instead of recording distance,
          color[v] = 1-color[u];        // we just record two colors {0, 1}
          q.push(v);
        }
        else if (color[v] == color[u]) {       // u & v have the same color
          isBipartite = false;               // we have a coloring conflict
          break;
        }
      }
    }
    printf("%sBICOLORABLE.\n", (isBipartite ? "" : "NOT "));
  }
  return 0;
}
