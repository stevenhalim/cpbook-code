/* UVa 10003
   
   O(N^2) with Knuth-Yao dp optimization

   Top-down implementation
*/

#include <bits/stdc++.h>
using namespace std;

int l, n, A[55], memo[55][55];
int opt[55][55];

int cut(int left, int right) {
  if (left+1 >= right) {
    opt[left][right] = right;
    return 0;
  }
  int &ans = memo[left][right];
  if (ans != -1) return ans;
  ans = 2e9;
  cut(left,right-1);
  cut(left+1,right);
  for (int i = opt[left][right-1]; i <= opt[left+1][right]; ++i) {
    int value = cut(left, i) + cut(i, right) + (A[right]-A[left]);
    if ( value < ans ) {
      ans = value;
      opt[left][right] = i;
    }
  }
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
    memset(opt, -1, sizeof(opt));
    printf("The minimum cutting is %d.\n", cut(0, n+1)); // start with left = 0 and right = n+1
  }
  return 0;
}
