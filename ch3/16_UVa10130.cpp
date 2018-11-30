// SuperSale 

// 0-1 Knapsack DP (Top-Down, faster)

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1010
#define MAX_W 40

int N, V[MAX_N], W[MAX_N], memo[MAX_N][MAX_W];

int value(int id, int w) {
  if (id == N || w == 0) return 0;
  if (memo[id][w] != -1) return memo[id][w];
  if (W[id] > w)         return memo[id][w] = value(id + 1, w);
  return memo[id][w] = max(value(id + 1, w), V[id] + value(id + 1, w - W[id]));
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    memset(memo, -1, sizeof memo);
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
      scanf("%d %d", &V[i], &W[i]);
    int ans = 0;
    int G; scanf("%d", &G);
    while (G--) {
      int MW; scanf("%d", &MW);
      ans += value(0, MW);
    }
    printf("%d\n", ans);
  }
  return 0;
}

/*

// 0-1 Knapsack DP (Bottom-Up)

#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1010
#define MAX_W 40

int V[MAX_N], W[MAX_N], C[MAX_N][MAX_W];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int N; scanf("%d", &N);
    for (int i = 1; i<= N; i++)
      scanf("%d %d", &V[i], &W[i]);
    int ans = 0;
    int G; scanf("%d", &G);
    while (G--) {
      int MW; scanf("%d", &MW);
      for (int i = 0; i <= N;  i++) C[i][0] = 0;
      for (int w = 0; w <= MW; w++) C[0][w] = 0;
      for (int i = 1; i <= N; i++)
        for (int w = 1; w <= MW; w++) {
          if (W[i] > w) C[i][w] = C[i-1][w];
          else          C[i][w] = max(C[i-1][w], V[i] + C[i-1][w-W[i]]);
        }
      ans += C[N][MW];
    }
    printf("%d\n", ans);
  }
  return 0;
}

*/
