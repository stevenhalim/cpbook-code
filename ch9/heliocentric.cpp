// Heliocentric

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int mod(ll a, int m) {                           // returns a (mod m)
  return ((a%m) + m) % m;                        // ensure positive answer
}

int extEuclid(int a, int b, int &x, int &y) {    // pass x and y by ref
  int xx = y = 0;
  int yy = x = 1;
  while (b) {                                    // repeats until b == 0
    int q = a/b;
    tie(a, b) = tuple(b, a%b);
    tie(x, xx) = tuple(xx, x-q*xx);
    tie(y, yy) = tuple(yy, y-q*yy);
  }
  return a;                                      // returns gcd(a, b)
}

int modInverse(int b, int m) {                   // returns b^(-1) (mod m)
  int x, y;
  int d = extEuclid(b, m, x, y);                 // to get b*x + m*y == d
  if (d != 1) return -1;                         // to indicate failure
  // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
  return mod(x, m);
}

int crt(vi r, vi m) {
  // m_t = m_0*m_1*...*m_{n-1}
  int mt = accumulate(m.begin(), m.end(), 1, multiplies<>());
  int x = 0;
  for (int i = 0; i < (int)m.size(); ++i) {
    int a = mod((ll)r[i] * modInverse(mt/m[i], m[i]), m[i]);
    x = mod(x + (ll)a * (mt/m[i]), mt);
  }
  return x;
}

int main() {
  int e, m, caseNo = 0;
  while (scanf("%d %d", &e, &m) != EOF) {
    // Complete Search way, ans is in [0..365*687) or in [0..250755)
    // int ans = 0;
    // while (!(e == 0 && m == 0)) { // repeat until e == m == 0, will stop after at most 250755 iterations
    //   e = (e+1)%365;
    //   m = (m+1)%687;
    //   ++ans;
    // }

    // Chinese Remainder Theorem way
    // ans = 365-e (mod 365)
    // ans = 687-m (mod 687)
    // 365 and 687 are coprime, mt = 365*687 = 250755
    vi orbit({365, 687}); // the number of days of earth and mars orbits, respectively, gcd(365, 687) = 1, pairwise coprime
    // vi r({-e, -m}); // this works too as -e = 365-e (mod 365) and -m = 687-m (mod 687)
    vi r({365-e, 687-m});
    int ans = crt(r, orbit);

    printf("Case %d: %d\n", ++caseNo, ans);
  }
  return 0;
}
