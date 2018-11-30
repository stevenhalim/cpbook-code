/* How do you add? */

// top-down

/*
#include <cstdio>
#include <cstring>
using namespace std;

int N, K, memo[110][110];

int ways(int N, int K) {
  if (K == 1) // only can use 1 number to add up to N
    return 1; // the answer is definitely 1, that number itself
  else if (memo[N][K] != -1)
    return memo[N][K];

  // if K > 1, we can choose one number from [0..N] to be one of the number and recursively compute the rest
  int total_ways = 0;
  for (int split = 0; split <= N; split++)
    total_ways = (total_ways + ways(N - split, K - 1)) % 1000000; // we just need the modulo 1M
  return memo[N][K] = total_ways; // memoize them
}

int main() {
  memset(memo, -1, sizeof memo);
  while (scanf("%d %d", &N, &K), (N || K)) // some recursion formula + top down DP
    printf("%d\n", ways(N, K));
  return 0;
}
*/



// bottom-up

#include <cstdio>
#include <cstring>
using namespace std;

int main() {
  int i, j, split, dp[110][110], N, K;

  memset(dp, 0, sizeof dp);

  for (i = 0; i <= 100; i++) // these are the base cases
    dp[i][1] = 1;

  for (j = 1; j < 100; j++) // these three nested loops form the correct topological order
    for (i = 0; i <= 100; i++)
      for (split = 0; split <= 100 - i; split++) {
        dp[i + split][j + 1] += dp[i][j];
        dp[i + split][j + 1] %= 1000000;
      }

  while (scanf("%d %d", &N, &K), (N || K))
    printf("%d\n", dp[N][K]);

  return 0;
}
