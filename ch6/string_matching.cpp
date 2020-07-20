#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200010;

char T[MAX_N], P[MAX_N];                         // T = text, P = pattern
int n, m;                                        // n = |T|, m = |P|

// Knuth-Morris-Pratt's algorithm specific code
int b[MAX_N];                                    // b = back table

int naiveMatching() {
  int freq = 0;
  for (int i = 0; i < n; ++i) {                  // try all starting index
    bool found = true;
    for (int j = 0; (j < m) && found; ++j)
      if ((i+j >= n) || (P[j] != T[i+j]))        // if mismatch found
        found = false;                           // abort this, try i+1
    if (found) {                                 // T[i..i+m-1] = P[0..m-1]
      ++freq;
      // printf("P is found at index %d in T\n", i);
    }
  }
  return freq;
}

void kmpPreprocess() {                           // call this first
  int i = 0, j = -1; b[0] = -1;                  // starting values
  while (i < m) {                                // pre-process P
    while ((j >= 0) && (P[i] != P[j])) j = b[j]; // different, reset j
    ++i; ++j;                                    // same, advance both
    b[i] = j;
  }
}

int kmpSearch() {                               // similar as above
  int freq = 0;
  int i = 0, j = 0;                              // starting values
  while (i < n) {                                // search through T
    while ((j >= 0) && (T[i] != P[j])) j = b[j]; // if different, reset j
    ++i; ++j;                                    // if same, advance both
    if (j == m) {                                // a match is found
      ++freq;
      // printf("P is found at index %d in T\n", i-j);
      j = b[j];                                  // prepare j for the next
    }
  }
  return freq;
}

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
  return (x+m)%m;                                // this is the answer
}

int hash_fast(int L, int R) {                    // O(1) hash of any substr
  if (L == 0) return h[R];                       // h is the prefix hashes
  int ans = 0;
  ans = ((h[R] - h[L-1]) % M + M) % M;           // compute differences
  ans = ((ll)ans * modInverse(Pow[L], M)) % M;   // remove P[L]^-1 (mod M)
  return ans;
}

int main() {
  // strcpy(T, "I DO NOT LIKE SEVENTY SEV BUT SEVENTY SEVENTY SEVEN");
  // strcpy(P, "SEVENTY SEVEN");
  int extreme_limit = 100000; // experiment time is about 10s+ total
  for (int i = 0; i < extreme_limit-1; ++i) T[i] = 'A'+rand()%2;
  T[extreme_limit-2] = 'B';
  T[extreme_limit-1] = 0;
  for (int i = 0; i < 100; ++i) P[i] = 'A'+rand()%2;
  P[10] = 0;
  n = (int)strlen(T);
  m = (int)strlen(P);

  //if the end of line character is read too, uncomment the line below
  //T[n-1] = 0; n--; P[m-1] = 0; m--;

  // printf("T = '%s'\n", T);
  // printf("P = '%s'\n", P);
  // printf("\n");

  clock_t t0 = clock();
  printf("String Library, #match = ");
  char *pos = strstr(T, P);
  int freq = 0;
  while (pos != NULL) {
    ++freq;
    // printf("P is found at index %d in T\n", pos-T);
    pos = strstr(pos+1, P);
  }
  printf("%d\n", freq);
  clock_t t1 = clock();
  printf("Runtime = %.10lf s\n\n", (t1-t0) / (double) CLOCKS_PER_SEC);

  printf("Naive Matching, #match = ");
  printf("%d\n", naiveMatching());
  clock_t t2 = clock();
  printf("Runtime = %.10lf s\n\n", (t2-t1) / (double) CLOCKS_PER_SEC);

  printf("Rabin-Karp, #match = ");
  computeRollingHash();                          // use Rolling Hash
  int hP = 0;
  for (int i = 0; i < m; ++i)                    // O(n)
    hP = (hP + (ll)P[i]*Pow[i]) % M;
  freq = 0;
  for (int i = 0; i <= n-m; ++i)                 // try all starting pos
    if (hash_fast(i, i+m-1) == hP) {             // a possible match
      ++freq;
      // printf("P is found at index %d in T\n", i);
    }
  printf("%d\n", freq);
  clock_t t3 = clock();
  printf("Runtime = %.10lf s\n\n", (t3-t2) / (double) CLOCKS_PER_SEC);

  printf("Knuth-Morris-Pratt, #match = ");
  kmpPreprocess();
  printf("%d\n", kmpSearch());
  clock_t t4 = clock();
  printf("Runtime = %.10lf s\n\n", (t4-t3) / (double) CLOCKS_PER_SEC);

  return 0;
}
