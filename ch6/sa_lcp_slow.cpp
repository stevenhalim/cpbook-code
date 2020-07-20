#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

const int MAX_N = 2510;                          // O(n^2 log n)

char T[MAX_N];                                   // up to 2500 chars

int main() {
  freopen("sa_lcp_in.txt", "r", stdin);
  scanf("%s", &T);                               // read T
  int n = (int)strlen(T);                        // count n
  T[n++] = '$';                                  // add terminating symbol

  vi SA(n);
  iota(SA.begin(), SA.end(), 0);                 // the initial SA
  // analysis of this sort below: O(n log n) * cmp: O(n) = O(n^2 log n)
  sort(SA.begin(), SA.end(), [](int a, int b) {  // O(n^2 log n)
    return strcmp(T+a, T+b) < 0;
  });                                            // continued below

  vi LCP(n);
  LCP[0] = 0;                                    // default value
  for (int i = 1; i < n; ++i) {                  // compute by def, O(n^2)
    int L = 0;                                   // always reset L to 0
    while ((SA[i]+L < n) && (SA[i-1]+L < n) &&
           (T[SA[i]+L] == T[SA[i-1]+L])) ++L;    // same L-th char, ++L
    LCP[i] = L;
  }

  printf("T = '%s'\n", T);
  printf(" i SA[i] LCP[i]   Suffix SA[i]\n");
  for (int i = 0; i < n; ++i)
    printf("%2d    %2d    %2d    %s\n", i, SA[i], LCP[i], T+SA[i]);

  return 0;
}
