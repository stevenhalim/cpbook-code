// 15-Puzzle Problem with IDA*

#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

#define INF 1000000000
#define ROW_SIZE 4 // ROW_SIZE is a matrix of 4 x 4
#define PUZZLE (ROW_SIZE*ROW_SIZE)
#define X 15

int p[PUZZLE];
int lim, nlim;
int dr[] = { 0,-1, 0, 1}; // E,N,W,S
int dc[] = { 1, 0,-1, 0}; // R,U,L,D
map<int, int> pred;
map<unsigned long long, int> vis;
char ans[] = "RULD";

inline int h1() { // heuristic: sum of Manhattan distances (compute all)
  int ans = 0;
  for (int i = 0; i < PUZZLE; i++) {
    int tgt_i = p[i] / 4, tgt_j = p[i] % 4;
    if (p[i] != X)
      ans += abs(i / 4 - tgt_i) + abs(i % 4 - tgt_j); // Manhattan distance
  }
  return ans;
}

inline int h2(int i1, int j1, int i2, int j2) { // heuristic: sum of manhattan distances (compute delta)
  int tgt_i = p[i2 * 4 + j2] / 4, tgt_j = p[i2 * 4 + j2] % 4;
  return -(abs(i2 - tgt_i) + abs(j2 - tgt_j)) + (abs(i1 - tgt_i) + abs(j1 - tgt_j));
}

inline bool goal() {
  for (int i = 0; i < PUZZLE; i++)
    if (p[i] != X && p[i] != i)
      return false;
  return true;
}

inline bool valid(int r, int c) {
  return 0 <= r && r < 4 && 0 <= c && c < 4;
}

inline void swap(int i, int j, int new_i, int new_j) {
  int temp = p[i * 4 + j];
  p[i * 4 + j] = p[new_i * 4 + new_j];
  p[new_i * 4 + new_j] = temp;
}

bool DFS(int g, int h) {
  if (g + h > lim) {
    nlim = min(nlim, g + h);
    return false;
  }

  if (goal())
    return true;

  unsigned long long state = 0;
  for (int i = 0; i < PUZZLE; i++) { // transform 16 numbers into 64 bits, exactly into ULL
    state <<= 4; // move left 4 bits
    state += p[i]; // add this digit (max 15 or 1111)
  }

  if (vis.count(state) && vis[state] <= g) // not pure backtracking... this is to prevent cycling
    return false; // not good
  vis[state] = g; // mark this as visited

  int i, j, d, new_i, new_j;
  for (i = 0; i < PUZZLE; i++)
    if (p[i] == X)
      break;
  j = i % 4;
  i /= 4;

  for (d = 0; d < 4; d++) {
    new_i = i + dr[d]; new_j = j + dc[d];
    if (valid(new_i, new_j)) {
      int dh = h2(i, j, new_i, new_j);
      swap(i, j, new_i, new_j); // swap first
      pred[g + 1] = d;
      if (DFS(g + 1, h + dh)) // if ok, no need to restore, just go ahead
        return true;
      swap(i, j, new_i, new_j); // restore
    }
  }

  return false;
}

int IDA_Star() {
  lim = h1();
  while (true) {
    nlim = INF; // next limit
    pred.clear();
    vis.clear();
    if (DFS(0, h1()))
      return lim; 
    if (nlim == INF)
      return -1;
    lim = nlim; // nlim > lim
    if (lim > 45) // pruning condition in the problem
      return -1;
  }
}

void output(int d) {
  if (d == 0)
    return;
  output(d - 1);
  printf("%c", ans[pred[d]]);
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
#endif

  int N;
  scanf("%d", &N);
  while (N--) {
    int i, j, blank = 0, sum = 0, ans = 0;
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++) {
        scanf("%d", &p[i * 4 + j]);
        if (p[i * 4 + j] == 0) {
          p[i * 4 + j] = X; // change to X (15)
          blank = i * 4 + j; // remember the index
        }
        else
          p[i * 4 + j]--; // use 0-based indexing
      }

    for (i = 0; i < PUZZLE; i++)
      for (j = 0; j < i; j++)
        if (p[i] != X && p[j] != X && p[j] > p[i])
          sum++;
    sum += blank / ROW_SIZE;

    if (sum % 2 != 0 && ((ans = IDA_Star()) != -1))
      output(ans), printf("\n");
    else
      printf("This puzzle is not solvable.\n");
  }

  return 0;
}
