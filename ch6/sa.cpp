#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

const int MAX_N = 100010;                        // up to 100K characters

char T[MAX_N];                                   // the input string
int n;                                           // the length of T
int RA[MAX_N], tempRA[MAX_N];                    // rank array
int SA[MAX_N], tempSA[MAX_N];                    // suffix array
int c[MAX_N];                                    // for counting/radix sort

char P[MAX_N];                                   // the pattern string
int m;                                           // the length of P

int Phi[MAX_N];                                  // for computing LCP
int PLCP[MAX_N];
// LCP[i] = the LCP between previous suffix T+SA[i-1] and suffix T+SA[i]
int LCP[MAX_N];

bool cmp(int a, int b) { return strcmp(T+a, T+b) < 0; } // compare

void constructSA_slow() {                        // max ~1000 characters
  for (int i = 0; i < n; ++i) SA[i] = i;         // this is the initial SA
  sort(SA, SA+n, cmp); // sort: O(n log n) * compare: O(n) = O(n^2 log n)
}

void countingSort(int k) {                       // O(n)
  int i, sum, maxi = max(300, n);                // up to 255 ASCII chars
  memset(c, 0, sizeof c);                        // clear frequency table
  for (i = 0; i < n; ++i)                        // count the frequency
    ++c[i+k < n ? RA[i+k] : 0];                  // of each integer rank
  for (i = sum = 0; i < maxi; ++i) {
    int t = c[i]; c[i] = sum; sum += t;
  }
  for (i = 0; i < n; ++i)                        // shuffle SA
    tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
  for (i = 0; i < n; ++i)                        // update SA
    SA[i] = tempSA[i];
}

void constructSA() {                             // can go up to 100K chars
  int i, k, r;
  for (i = 0; i < n; ++i) RA[i] = T[i];          // initial rankings
  for (i = 0; i < n; ++i) SA[i] = i;             // initial SA
  for (k = 1; k < n; k <<= 1) {                  // repeat log n times
    // this is actually radix sort: sort based on the second item
    // and then (stable) sort based on the first item
    countingSort(k);                             
    countingSort(0);
    tempRA[SA[0]] = r = 0;                       // re-ranking process
    for (i = 1; i < n; ++i)                      // compare adj suffixes
      tempRA[SA[i]] = // if same pair => same rank r; otherwise, increase r
      (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
    for (i = 0; i < n; ++i)                      // update RA
      RA[i] = tempRA[i];
    if (RA[SA[n-1]] == n-1) break;               // nice optimization
  }
}

void computeLCP_slow() {
  LCP[0] = 0;                                    // default value
  for (int i = 1; i < n; ++i) {                  // compute LCP by def
    int L = 0;                                   // always reset L to 0
    while (T[SA[i]+L] == T[SA[i-1]+L]) ++L;      // same L-th char, ++L
    LCP[i] = L;
  }
}

void computeLCP() {
  int i, L;
  Phi[SA[0]] = -1;                               // default value
  for (i = 1; i < n; ++i)                        // compute Phi in O(n)
    Phi[SA[i]] = SA[i-1];                        // remember prev suffix
  for (i = L = 0; i < n; ++i) {                  // compute PLCP in O(n)
    if (Phi[i] == -1) { PLCP[i] = 0; continue; } // special case
    while (T[i+L] == T[Phi[i]+L]) ++L;           // L incr max n times
    PLCP[i] = L;
    L = max(L-1, 0);                             // L dec max n times
  }
  for (i = 0; i < n; ++i)                        // compute LCP in O(n)
    LCP[i] = PLCP[SA[i]];                        // restore PLCP
}

ii stringMatching() {                            // in O(m log n)
  int lo = 0, hi = n-1, mid = lo;                // range = [0..n-1]
  while (lo < hi) {                              // find lower bound
    mid = (lo+hi) / 2;                           // this is round down
    int res = strncmp(T+SA[mid], P, m);          // find P in suffix 'mid'
    (res >= 0) ? hi = mid : lo = mid+1;          // notice the >= sign
  }
  if (strncmp(T+SA[lo], P, m) != 0) return ii(-1, -1); // if not found
  ii ans; ans.first = lo;
  lo = 0; hi = n-1; mid = lo;
  while (lo < hi) {                              // now find upper bound
    mid = (lo+hi) / 2;
    int res = strncmp(T+SA[mid], P, m);
    (res > 0) ? hi = mid : lo = mid+1;           // notice the > sign
  }
  if (strncmp(T+SA[hi], P, m) != 0) --hi;        // special case
  ans.second = hi;
  return ans;
} // return lower/upperbound as first/second item of the pair, respectively

ii LRS() {  // returns a pair (the LRS length and its index)
  int i, idx = 0, maxLCP = -1;
  for (i = 1; i < n; ++i)                        // O(n), start from i = 1
    if (LCP[i] > maxLCP)
      maxLCP = LCP[i], idx = i;
  return ii(maxLCP, idx);
}

int owner(int idx) { return (idx < n-m-1) ? 1 : 2; }

ii LCS() {                 // returns a pair (the LCS length and its index)
  int i, idx = 0, maxLCP = -1;
  for (i = 1; i < n; ++i)                         // O(n), start from i = 1
    if (owner(SA[i]) != owner(SA[i-1]) && LCP[i] > maxLCP)
      maxLCP = LCP[i], idx = i;
  return ii(maxLCP, idx);
}

int main() {
  //printf("Enter a string T below, we will compute its Suffix Array:\n");
  strcpy(T, "ACGACGGCTGCGGTAACCC#TTACGGCTGCGGTCCCCTT@CCCCCCGTTTACGGCTGCGGTGG$");
  n = (int)strlen(T);
  // T[n++] = '$';
  // if '\n' is read, uncomment the next line
  //T[n-1] = '$'; T[n] = 0;

/*
  constructSA_slow();                                       // O(n^2 log n)
  printf("The Suffix Array of string T = '%s' is shown below (O(n^2 log n) version):\n", T);
  printf("i\tSA[i]\tSuffix\n");
  for (int i = 0; i < n; i++) printf("%2d\t%2d\t%s\n", i, SA[i], T + SA[i]);
*/
  constructSA();                                              // O(n log n)
  printf("\nThe Suffix Array of string T = '%s' is shown below (O(n log n) version):\n", T);
  computeLCP();                                                     // O(n)

  printf("i\tSA[i]\tLCP[i]\tSuffix\n");
  for (int i = 0; i < n; i++) printf("%2d\t%2d\t%2d\t%s\n", i, SA[i], LCP[i], T+SA[i]);

  // LRS demo
  ii ans = LRS();                 // find the LRS of the first input string
  char lrsans[MAX_N];
  strncpy(lrsans, T + SA[ans.second], ans.first);
  printf("\nThe LRS is '%s' with length = %d\n\n", lrsans, ans.first);

/*
  // stringMatching demo
  //printf("\nNow, enter a string P below, we will try to find P in T:\n");
  strcpy(P, "A");
  m = (int)strlen(P);
  // if '\n' is read, uncomment the next line
  //P[m-1] = 0; m--;
  ii pos = stringMatching();
  if (pos.first != -1 && pos.second != -1) {
    printf("%s is found SA[%d..%d] of %s\n", P, pos.first, pos.second, T);
    printf("They are:\n");
    for (int i = pos.first; i <= pos.second; i++)
      printf("  %s\n", T + SA[i]);
  } else printf("%s is not found in %s\n", P, T);

  // LCS demo
  //printf("\nRemember, T = '%s'\nNow, enter another string P:\n", T);
  // T already has '$' at the back
  strcpy(P, "CATA");
  m = (int)strlen(P);
  // if '\n' is read, uncomment the next line
  //P[m-1] = 0; m--;
  strcat(T, P);                                                 // append P
  strcat(T, "#");                                    // add '$' at the back
  n = (int)strlen(T);                                           // update n

  // reconstruct SA of the combined strings
  constructSA();                                              // O(n log n)
  computeLCP();                                                     // O(n)
  printf("\nThe LCP information of 'T+P' = '%s':\n", T);
  printf("i\tSA[i]\tLCP[i]\tOwner\tSuffix\n");
  for (int i = 0; i < n; i++)
    printf("%2d\t%2d\t%2d\t%2d\t%s\n", i, SA[i], LCP[i], owner(SA[i]), T + SA[i]);

  ans = LCS();         // find the longest common substring between T and P
  char lcsans[MAX_N];
  strncpy(lcsans, T + SA[ans.second], ans.first);
  printf("\nThe LCS is '%s' with length = %d\n", lcsans, ans.first);
*/
  
  return 0;
}
