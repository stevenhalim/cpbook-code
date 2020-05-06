#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200010;

char T[MAX_N], P[MAX_N];                         // T = text, P = pattern
int n, m;                                        // n = |T|, m = |P|

// Rabin-Karp's algorithm specific code
typedef long long ll;

const int p = 131;                               // p and M are
const int M = 1e9+7;                             // relatively prime

int Pow[MAX_N];                                  // to store p^i % M
int h[MAX_N];                                    // to store prefix hashes

void computeRollingHash() {                      // Overall: O(n)
  Pow[0] = 1;                                    // compute p^i % M
  for (int i = 1; i < n; ++i)                    // O(n)
    Pow[i] = ((ll)Pow[i-1]*p) % M;
  h[0] = 0;
  for (int i = 0; i < n; ++i) {                  // O(n)
    if (i != 0) h[i] = h[i-1];                   // rolling hash
    h[i] = (h[i] + ((ll)T[i]*Pow[i]) % M) % M;
  }
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
  ans = ((ll)ans * modInverse(Pow[L], M)) % M;   // remove P[L]^-1 (mod M)
  // ans = (ans + M) % M;
  return ans;
}

int main() {
  // strcpy(T, "ABCBC");
  // strcpy(P, "BC");                               // should be 1 and 3
  int extreme_limit = 2000;
  for (int i = 0; i < extreme_limit-1; ++i) T[i] = 'A'+rand()%2;
  T[extreme_limit-1] = 0;
  for (int i = 0; i < extreme_limit/5; ++i) P[i] = 'A'+rand()%2;
  P[extreme_limit/5-1] = 0;
  n = (int)strlen(T);
  m = (int)strlen(P);

  printf("T = '%s'\n", T);
  printf("P = '%s'\n", P);
  printf("\n");

  computeRollingHash();                          // use Rolling Hash
  // printf("%d\n", hash_fast(0, n-1));             // O(1) computation

  for (int i = 0; i < n; ++i)                    // all pairs must match
    for (int j = i; j < n; ++j) {
      int hash_slow = 0;
      for (int k = i; k <= j; ++k)               // O(n)
        hash_slow = (hash_slow + (ll)T[k]*Pow[k-i]) % M;
      if (hash_slow != hash_fast(i, j)) {
        printf("%d-%d, %d vs %d\n", i, j, hash_slow, hash_fast(i, j));
      }
    }

  // Rabin Karp's String Matching algorithm
  int hP = 0;
  for (int i = 0; i < m; ++i)                    // O(n)
    hP = (hP + (ll)P[i]*Pow[i]) % M;
  // printf("P is found at indices:");
  int freq = 0;
  for (int i = 0; i <= n-m; ++i)                 // try all starting pos
    if (hash_fast(i, i+m-1) == hP)               // a possible match
      ++freq;
      // printf(" %d", i);
  printf("%d\n", freq);
  printf("\n");

  return 0;
}
