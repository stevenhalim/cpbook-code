// Fire! Fire!! Fire!!!

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int memo[1010][2];
vector<vi> AL;                                   // undirected version
vector<vi> Children;                             // directed version
vi vis;

void dfs(int u) {
  vis[u] = true;
  for (auto &v : AL[u])
    if (!vis[v]) {
      Children[u].push_back(v);                  // now u<->v becomes u->v
      dfs(v);
    }
}

int MVC(int u, int flag) {                       // get |MVC| on Tree
  int &ans = memo[u][flag];
  if (ans != -1) return ans;                     // top down DP
  if ((int)Children[u].size() == 0)              // u is a leaf
    ans = flag;                                  // 1/0 = taken/not
  else if (flag == 0) {                          // if u is not taken,
    ans = 0;                                     // we must take
    for (auto &v : Children[u])                  // all its children
      ans += MVC(v, 1);
  }
  else if (flag == 1) {                          // if u is taken,
    ans = 1;                                     // we take the minimum
    for (auto &v : Children[u])                  // between taking or
      ans += min(MVC(v, 1), MVC(v, 0));          // not taking its children
  }
  return ans;
}

int main() {
  int N;
  while (scanf("%d", &N), N) {
    AL.assign(N, vi());
    Children.assign(N, vi());
    for (int u = 0; u < N; ++u) { // Adj List of each vertex, 0-based
      int ni; scanf("%d", &ni);
      while (ni--) {
        int v; scanf("%d", &v); --v; // 0-based indexing
        AL[u].push_back(v);
      }
    }
    if (N == 1) { // special case
      printf("1\n"); // still need 1 fire exit
      continue;
    }
    vis.assign(N, 0);
    dfs(0); // root the tree at vertex 0
    memset(memo, -1, sizeof memo);
    printf("%d\n", min(MVC(0, 1), MVC(0, 0)));
  }
  return 0;
}
