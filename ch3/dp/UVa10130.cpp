// SuperSale 

// 0-1 Knapsack DP (Top-Down, faster)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1010;
const int MAX_W = 40;

int N, V[MAX_N], W[MAX_N], memo[MAX_N][MAX_W];

int dp(int id, int remW) {
  if ((id == N) || (remW == 0)) return 0;        // two base cases
  int &ans = memo[id][remW];
  if (ans != -1) return ans;                     // computed before
  if (W[id] > remW) return ans = dp(id+1, remW); // no choice, skip
  return ans = max(dp(id+1, remW),               // has choice, skip
                   V[id]+dp(id+1, remW-W[id]));  // or take
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    memset(memo, -1, sizeof memo);
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
      scanf("%d %d", &V[i], &W[i]);
    int ans = 0;
    int G; scanf("%d", &G);
    while (G--) {
      int MW; scanf("%d", &MW);
      ans += dp(0, MW);
    }
    printf("%d\n", ans);
  }
  return 0;
}

/*

// 0-1 Knapsack DP (Bottom-Up)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1010;
const int MAX_W = 40;

int V[MAX_N], W[MAX_N], C[MAX_N][MAX_W];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int N; scanf("%d", &N);
    for (int i = 1; i<= N; ++i)
      scanf("%d %d", &V[i], &W[i]);
    int ans = 0;
    int G; scanf("%d", &G);
    while (G--) {
      int MW; scanf("%d", &MW);
      for (int i = 0; i <= N;  ++i) C[i][0] = 0;
      for (int w = 0; w <= MW; ++w) C[0][w] = 0;
      for (int i = 1; i <= N; ++i)
        for (int w = 1; w <= MW; ++w) {
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
