// Cutting Sticks
// Top-Down DP

#include <bits/stdc++.h>
using namespace std;

int l, n, A[55], memo[55][55];

int cut(int left, int right) {
  if (left+1 == right) return 0;
  int &ans = memo[left][right];
  if (ans != -1) return ans;
  ans = 2e9;
  for (int i = left+1; i < right; ++i)
    ans = min(ans, cut(left, i) + cut(i, right) + (A[right]-A[left]));
  return ans;
}

int main() {
  while (scanf("%d", &l), l) {
    A[0] = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &A[i]);
    A[n+1] = l;
    memset(memo, -1, sizeof memo);
    printf("The minimum cutting is %d.\n", cut(0, n+1)); // start with left = 0 and right = n+1
  }
  return 0;
}
