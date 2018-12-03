#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1000

vector<vector<int>> children;

int L[2*MAX_N], E[2*MAX_N], H[MAX_N], idx;

void dfs(int cur, int depth) {
  H[cur] = idx;
  E[idx] = cur;
  L[idx++] = depth;
  for (auto &nxt : children[cur]) {
    dfs(nxt, depth+1);
    E[idx] = cur;                              // backtrack to current node
    L[idx++] = depth;
} }

void buildRMQ() {
  idx = 0;
  memset(H, -1, sizeof H);
  dfs(0, 0);                       // we assume that the root is at index 0
}

int main() {
  children.assign(10, vector<int>());
  children[0].push_back(1); children[0].push_back(7);
  children[1].push_back(2); children[1].push_back(3); children[1].push_back(6);
  children[3].push_back(4); children[3].push_back(5);
  children[7].push_back(8); children[7].push_back(9);

  buildRMQ();
  for (int i = 0; i < 2*10-1; i++) printf("%d ", H[i]);
  printf("\n");
  for (int i = 0; i < 2*10-1; i++) printf("%d ", E[i]);
  printf("\n");
  for (int i = 0; i < 2*10-1; i++) printf("%d ", L[i]);
  printf("\n");

  return 0;
}
