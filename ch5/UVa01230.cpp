// 0.000s in C++

#include <bits/stdc++.h>
using namespace std;

int mod(int a, int m) { return ((a%m)+m) % m; }  // ensure positive answer

int slow_modPow(int b, int p, int m) {           // assume 0 <= b < m
  int ans = 1;
  for (int i = 0; i < p; ++i)                    // this is O(p)
    ans = mod(ans*b, m);                         // ans always in [0..m-1]
  return ans;
}

int modPow(int b, int p, int m) {                // assume 0 <= b < m
  if (p == 0) return 1;
  int ans = modPow(b, p/2, m);                   // this is O(log p)
  ans = mod(ans*ans, m);                         // double it first
  if (p&1) ans = mod(ans*b, m);                  // *b if p is odd
  return ans;                                    // ans always in [0..m-1]
}

int main() {
  ios::sync_with_stdio(false); cin.tie(NULL);
  // for comparison only
  // for (int b = 0; b <= 100; ++b)
  //   for (int p = 0; p <= 100; ++p)
  //     assert(slow_modPow(b, p, 997) == modPow(b, p, 997));
  int c; cin >> c;
  while (c--) {
    int x, y, n; cin >> x >> y >> n;
    cout << modPow(x, y, n) << "\n";
  }
  return 0;
}
