// UVa 11450 - Wedding Shopping - Top Down
// this code is similar to recursive backtracking code
// parts of the code specific to top-down DP are commented with: `TOP-DOWN'
// if these lines are commented, this top-down DP will become backtracking!

#include <bits/stdc++.h>
using namespace std;

const int MAX_gm = 30; // up to 20 garments at most and 20 models/garment
const int MAX_M = 210; // maximum budget is 200

int M, C, price[MAX_gm][MAX_gm]; // price[g (<= 20)][k (<= 20)]
int memo[MAX_gm][MAX_M]; // TOP-DOWN: dp table [g (< 20)][money (<= 200)]

int dp(int g, int money) {
  if (money < 0) return -1e9;                    // fail, return -ve number
  if (g == C) return M-money;                    // we are done
  // if the line below is commented, top-down DP will become backtracking!!
  if (memo[g][money] != -1) return memo[g][money]; // TOP-DOWN: memoization
  int ans = -1;                                  // start with a -ve number
  for (int k = 1; k <= price[g][0]; ++k)         // try each model k
    ans = max(ans, dp(g+1, money-price[g][k]));
  return memo[g][money] = ans;                   // TOP-DOWN: memoize ans
}

/*
int dp(int g, money) {
  if (money < 0) return -1e9;                    // must check this first
  if (g == C) return M-money;                    // money can't be < 0
  int &ans = memo[g][money];                     // remember memory address
  if (ans != -1) return ans;
  for (int k = 1; k <= price[g][0]; ++k)         // try each model k
    ans = max(ans, dp(g+1, money-price[g][k]));
  return ans;                                    // ans == memo[g][money]
}

void print_dp(int g, money) {                    // void function
  if (g == C || money < 0) return;               // similar base cases
  for (int k = 1; k <= price[g][0]; ++k)         // which model k is opt?
    if (dp(g+1, money-price[g][k]) == memo[g][money]) { // this one
      printf("%d - ", price[g][k]);
      print_dp(g+1, money-price[g][k]);          // recurse to this only
      break;
    }
}
*/

int main() {                                     // easy to code
  int TC; scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &M, &C);
    for (int g = 0; g < C; ++g) {
      scanf("%d", &price[g][0]);                 // store k in price[g][0]
      for (int k = 1; k <= price[g][0]; ++k)
        scanf("%d", &price[g][k]);
    }
    memset(memo, -1, sizeof memo);               // TOP-DOWN: init memo
    if (dp(0, M) < 0) printf("no solution\n");   // start the top-down DP
    else              printf("%d\n", dp(0, M));
  }
  return 0;
}
