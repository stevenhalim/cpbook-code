// Bars

#include <bits/stdc++.h>
using namespace std;

#define MAX_n 20
#define LSOne(S) (S & (-S))

int main() {
  int t; scanf("%d", &t);
  while (t--) {
    int X; scanf("%d", &X);
    int n; scanf("%d", &n);
    int l[MAX_n];
    for (int i = 0; i < n; i++) scanf("%d", &l[i]);
    int i;
    for (i = 0; i < (1<<n); i++) {                   // for each subset, O(2^n)
      int sum = 0;
      // for (int j = 0; j < n; j++)                     // check membership, O(n)
      //   if (i & (1<<j))          // test if bit 'j' is turned on in subset 'i'?
      //     sum += l[j];                                   // if yes, process 'j'
      int mask = i;
      while (mask) {    // checking is now O(k), k is the # of bits that are on
        int two_pow_j = LSOne(mask);       // find the least significant on bit
        int j = __builtin_ctz(two_pow_j);
        sum += l[j];
        mask -= two_pow_j;
      }
      if (sum == X) break;                  // the answer is found: bitmask 'i'
    }
    printf(i < (1<<n) ? "YES\n" : "NO\n");
  }
  return 0;
}
