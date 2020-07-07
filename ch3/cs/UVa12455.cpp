// Bars

#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) (S & (-S))

const int MAX_n = 20;

int main() {
  int t; scanf("%d", &t);
  while (t--) {
    int X; scanf("%d", &X);
    int n; scanf("%d", &n);
    int l[MAX_n];
    for (int i = 0; i < n; ++i)
      scanf("%d", &l[i]);
    int i;
    for (i = 0; i < (1<<n); ++i) {               // for each subset, O(2^n)
      int sum = 0;
      // for (int j = 0; j < n; ++j)             // check membership, O(n)
      //   if (i & (1<<j))                       // see if bit 'j' is on?
      //     sum += l[j];                        // if yes, process 'j'
      int mask = i;                              // this is now O(k)
      while (mask) {                             // k is the # of on bits
        int two_pow_j = LSOne(mask);             // least significant bit
        int j = __builtin_ctz(two_pow_j);        // 2^j = two_pow_j, get j
        sum += l[j];
        mask -= two_pow_j;
      }
      if (sum == X) break;                       // the answer is found
    }
    printf(i < (1<<n) ? "YES\n" : "NO\n");
  }
  return 0;
}
