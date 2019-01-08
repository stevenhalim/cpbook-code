// UVa 11450 - Wedding Shopping - Top Down
// this code is similar to recursive backtracking code
// parts of the code specific to top-down DP are commented with: `TOP-DOWN'
// if these lines are commented, this top-down DP will become backtracking!

#include <bits/stdc++.h>
using namespace std;

#define MAX_gm 30  // 20 garments at most and 20 models per garment at most
#define MAX_M 210                                  // maximum budget is 200

int M, C, price[MAX_gm][MAX_gm];         // price[g (<= 20)][model (<= 20)]
int memo[MAX_gm][MAX_M];   // TOP-DOWN: dp table [g (< 20)][money (<= 200)]

int shop(int g, int money) {
  if (money < 0) return -1e9;  // fail, return a large -ve number, 1e9=10^9
  if (g == C) return M-money;          // we have bought last garment, done
  // if the line below is commented, top-down DP will become backtracking!!
  if (memo[g][money] != -1) return memo[g][money]; // TOP-DOWN: memoization
  int ans = -1;   // start with a -ve number as all prices are non negative
  for (int model = 1; model <= price[g][0]; model++)      // try all models
    ans = max(ans, shop(g+1, money-price[g][model]));
  return memo[g][money] = ans;       // TOP-DOWN: memoize ans and return it
}

/*
int shop(int g, money) {
  if (money < 0) return -1e9;  // order of multiple base cases is important
  if (g == C) return M-money;    // money can't be <0 if we reach this line
  int &ans = memo[g][money];                 // remember the memory address
  if (ans != -1) return ans;
  for (int model = 1; model <= price[g][0]; model++)
    ans = max(ans, shop(g+1, money-price[g][model]));
  return ans;                // ans (or memo[g][money]) is directly updated
}

void print_shop(int g, money) {   // this function does not return anything
  if (g == C || money < 0) return;                    // similar base cases
  for (int model = 1; model <= price[g][0]; model++) // which model is opt?
    if (shop(g+1, money-price[g][model]) == memo[g][money]) {   // this one
      printf("%d - ", price[g][model]);
      print_shop(g+1, money-price[g][model]);   // recurse to this one only
      break;
    }
}
*/

int main() {            // easy to code if you are already familiar with it
  int TC; scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &M, &C);
    for (int i = 0; i < C; i++) {
      scanf("%d", &price[i][0]);                  // store K in price[i][0]
      for (int j = 1; j <= price[i][0]; j++) scanf("%d", &price[i][j]);
    }
    memset(memo, -1, sizeof memo);   // TOP-DOWN: initialize memo to all -1
    if (shop(0, M) < 0) printf("no solution\n");   // start the top-down DP
    else                printf("%d\n", shop(0, M));
  }
  return 0;
}
