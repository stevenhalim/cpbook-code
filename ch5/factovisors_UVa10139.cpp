// Factovisors

#include <bits/stdc++.h>
using namespace std;

int vp(int p, int n) {                           // Legendre's formula
  int ans = 0;
  for (int pi = p; pi <= n; pi *= p)
    ans += n/pi;                                 // floor by default
  return ans;
}

int main() {
  int n, m;
  while (scanf("%d %d", &n, &m) != EOF) {
    bool possible;
         if (m == 0) possible = false;           // special case
    else if (m <= n) possible = true;            // always true
    else {                                       // factorize m
      unordered_map<int, int> factor_m;          // in any order
      int temp = m;
      int PF = 2;
      while ((temp > 1) && ((long long)PF*PF <= m)) {
        int freq = 0;
        while (temp%PF == 0) {                   // take out this factor
          ++freq;
          temp /= PF;
        }
        if (freq > 0) factor_m[PF] = freq;
        ++PF;                                    // next factor
      }
      if (temp > 1) factor_m[temp] = 1;

      possible = true;
      for (auto &[p, e] : factor_m)              // for each p^e in m
        if (vp(p, n) < e) {                      // has support in n!?
          possible = false;                      // ups, not enough
          break;
        }
    }

    printf("%d %s %d!\n", m, possible ? "divides" : "does not divide", n);
  }

  return 0;
}
