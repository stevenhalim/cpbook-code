// Bicoloring

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

const int INF = 1e9;

int main() {
  int n;
  while (scanf("%d", &n), n) {
    vector<vi> AL(n, vi());                      // notice: vi, not vii
    int l; scanf("%d", &l);
    while (l--) {
      int a, b; scanf("%d %d", &a, &b);
      AL[a].push_back(b);
      AL[b].push_back(a);                        // bidirectional
    }
    int s = 0;
    queue<int> q; q.push(s);
    vi color(n, INF); color[s] = 0;
    bool isBipartite = true;                     // add a Boolean flag
    while (!q.empty() && isBipartite) {          // as with original BFS
      int u = q.front(); q.pop();
      for (auto &v : AL[u]) {
        if (color[v] == INF) {                   // don't record distances
          color[v] = 1-color[u];                 // just record two colors
          q.push(v);
        }
        else if (color[v] == color[u]) {         // u & v have same color
          isBipartite = false;                   // a coloring conflict :(
          break;                                 // optional speedup
        }
      }
    }
    printf("%sBICOLORABLE.\n", (isBipartite ? "" : "NOT "));
  }
  return 0;
}
