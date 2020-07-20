#include <bits/stdc++.h>
using namespace std;

int mod(int a, int m) {                          // returns a (mod m)
  return ((a%m) + m) % m;                        // ensure positive answer
}

int modPow(int b, int p, int m) {                // assume 0 <= b < m
  if (p == 0) return 1;
  int ans = modPow(b, p/2, m);                   // this is O(log p)
  ans = mod(ans*ans, m);                         // double it first
  if (p&1) ans = mod(ans*b, m);                  // *b if p is odd
  return ans;                                    // ans always in [0..m-1]
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

int main() {
  // Fermat's little theorem, b^-1 = b^{m-2} (mod m)
  printf("%d\n", (27%7 * modPow(3, 5, 7)) % 7);  // example 1, output 2
  printf("%d\n", (27%7 * modPow(4, 5, 7)) % 7);  // example 2, output 5
  printf("%d\n", (520%18 * modPow(25, 16, 18)) % 18); // example 3, wrong answer, doesn't output 10 because 18 is not a prime

  // Using extEuclid
  printf("%d\n", (27%7 * modInverse(3, 7)) % 7); // example 1, output 2
  printf("%d\n", (27%7 * modInverse(4, 7)) % 7); // example 2, output 5
  printf("%d\n", (520%18 * modInverse(25, 18)) % 18); // example 3, output 10
  return 0;
}
