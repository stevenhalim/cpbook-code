#include <bits/stdc++.h>                         // a good practice in CP
using namespace std;                             // same as above
int main() {
  int a, b, c, n; scanf("%d %d %d %d", &a, &b, &c, &n); // bug fix below
  printf(((a >= 1) && (b >= 1) && (c >= 1) && (a+b+c >= n) && (n >= 3)) ?
         "YES\n" : "NO\n");                      // use ternary operator
  return 0;                                      // for shorter code
}
