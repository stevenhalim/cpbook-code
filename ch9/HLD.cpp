#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vector<vi> AL;                                   // undirected tree
vi par, heavy;

int heavy_light(int x) {                         // DFS traversal on tree
  int size = 1;
  int max_child_size = 0;
  for (auto &y : AL[x]) {                        // edge x->y
    if (y == par[x]) continue;                   // avoid cycle in a tree
    par[y] = x;
    int child_size = heavy_light(y);             // recurse
    if (child_size > max_child_size) {
      max_child_size = child_size;
      heavy[x] = y;                              // y is x's heaviest child
    }
    size += child_size;
  }
  return size;
}

vi group;

void decompose(int x, int p) {
  group[x] = p;                                  // x is in group p
  for (auto &y : AL[x]) {                        // edge x->y
    if (y == par[x]) continue;                   // avoid cycle in a tree
    if (y == heavy[x])
      decompose(y, p);                           // y is in group p
    else
      decompose(y, y);                           // y is in a new group y
  }
}

int main() {
  // as in Figure in HLD section, not yet rooted
  int N = 19;
  AL.assign(N,  {});
  AL[0] = {1, 2, 3};
  AL[1] = {0, 4};
  AL[2] = {0, 5, 6, 7};
  AL[3] = {0, 8};
  AL[4] = {1, 9, 10};
  AL[5] = {2};
  AL[6] = {2};
  AL[7] = {2, 11, 12};
  AL[8] = {3};
  AL[9] = {4};
  AL[10] = {4, 13};
  AL[11] = {7, 14};
  AL[12] = {7, 15};
  AL[13] = {10};
  AL[14] = {11, 16};
  AL[15] = {12, 17, 18};
  AL[16] = {14};
  AL[17] = {15};
  AL[18] = {15};

  par.assign(N, -1);
  heavy.assign(N, -1);
  heavy_light(0); // start modified DFS from root 0
  group.assign(N, -1);
  decompose(0, 0); // start labeling paths
  for (int i = 0; i < N; ++i)
    cout << setw(2) << i << ", parent = " << setw(2) << par[i] << ", heaviest child = " << setw(2) << heavy[i] << ", belong to heavy-paths group = " << group[i] << "\n";
  
  return 0;
}
