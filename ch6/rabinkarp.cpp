#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;

const int p = 131;                               // p and M are
const int M = 1e9+7;                             // relatively prime

vi P;                                            // to store p^i % M
vi h;                                            // to store prefix hashes

vi prepareP(int n) {                             // compute p^i % M
  P.assign(n, 0);
  P[0] = 1;
  for (int i = 1; i < n; ++i)                    // O(n)
    P[i] = ((ll)P[i-1]*p) % M;
  return P;
}

char convert(char ch) {
  // return ch-'A';                              // 'A'->0..'Z'->25
  return ch;                                     // 'A'->65..'Z'->90
}

int hash_slow(string T) {                        // Overall: O(n)
  int ans = 0;
  for (int i = 0; i < (int)T.length(); ++i)      // O(n)
    ans += ((ll)convert(T[i])*P[i]) % M;
  return ans;
}

vi computeRollingHash(string T) {                // Overall: O(n)
  vi P = prepareP((int)T.length());              // O(n)
  vi h(T.size(), 0);
  for (int i = 0; i < (int)T.length(); ++i) {    // O(n)
    if (i != 0) h[i] = h[i-1];                   // rolling hash
    h[i] = (h[i] + ((ll)T[i]*P[i]) % M) % M;
  }
  return h;
}

int extEuclid(int a, int b, int &x, int &y) {    // pass x and y by ref
  int xx = y = 0;
  int yy = x = 1;
  while (b) {                                    // repeats until b == 0
    int q = a/b;
    int t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
  return a;                                      // returns gcd(a, b)
}

int modInverse(int b, int m) {                   // returns b^(-1) (mod m)
  int x, y;
  int d = extEuclid(b, m, x, y);                 // to get b*x + m*y == d
  if (d != 1) return -1;                         // to indicate failure
  // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
  return (x+m)%m;                                // this is the answer
}

int hash_fast(int L, int R) {                    // O(1) hash of any substr
  if (L == 0) return h[R];                       // h is the prefix hashes
  int ans = 0;
  ans = ((h[R] - h[L-1]) % M + M) % M;           // compute differences
  ans = ((ll)ans * modInverse(P[L], M)) % M;     // remove P[L]^-1 (mod M)
  return ans;
}

int main() {
  string T = "ABCBC";
  int n = (int)T.length();

  P = prepareP(n);
  cout << hash_slow(T) << "\n";                  // O(n) computation

  h = computeRollingHash(T);                     // using Rolling Hash
  cout << hash_fast(0, n-1) << "\n";             // O(1) computation

  for (int i = 0; i < n; ++i)                    // all pairs must match
    for (int j = i; j < n; ++j)
      assert(hash_slow(T.substr(i, j-i+1)) == hash_fast(i, j));

  // Rabin Karp's String Matching algorithm
  string P = "BC";                               // should be 1 and 3
  int m = (int)P.length();
  int hP = hash_slow(P);                         // O(n), doesn't matter
  cout << P << " is found at indices:";
  for (int i = 0; i <= n-m; ++i)                 // try all starting pos
    if (hash_fast(i, i+m-1) == hP)               // a possible match
      cout << " " << i;
  cout << "\n";

  return 0;
}
