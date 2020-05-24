#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int n;
vi A;

void print_array(const char *s, vi &L, int n) {
  for (int i = 0; i < n; ++i) {
    if (i) printf(", ");
    else printf("%s: [", s);
    printf("%d", L[i]);
  }
  printf("]\n");
}

vi p;                                            // predecessor array

void print_LIS(int i) {                          // backtracking routine
  if (p[i] == -1) { printf("%d", A[i]); return; }// base case
  print_LIS(p[i]);                               // backtrack
  printf(" %d", A[i]);
}

int memo[10010];                                 // old limit: up to 10^4

int LIS(int i) {                                 // O(n^2) overall
  if (i == 0) return 1;
  int &ans = memo[i];
  if (ans != -1) return ans;                     // was computed before
  ans = 1;                                       // LIS can start anywhere
  for (int j = 0; j < i; ++j)                    // O(n) here
    if (A[j] < A[i])                             // increasing condition
      ans = max(ans, LIS(j)+1);                  // pick the max
  return ans;
}

int main() {
  // note: A[n-1] must be set as the largest value ("INF")
  // so that all LIS (that can start anywhere) will end at n-1
  srand(time(NULL));
  int n = 10+rand()%11;                          // [10..20]
  A.assign(n, 0);
  A[n-1] = 99;                                   // set A[n-1] = INF
  for (int i = 0; i < n-1; ++i)
    A[i] = rand()%101-50;                        // [-50..50]

  n = 12;
  vi sample({-7, 10, 9, 2, 3, 8, 8, 1, 2, 3, 4, 99});
  A = sample;

  printf("n = %d:", n);
  for (int i = 0; i < n; ++i)
    printf(" %d", A[i]);
  printf("\n");

  // early 2000 problems usually accept O(n^2) solution
  memset(memo, -1, sizeof memo);
  printf("LIS length is %d\n\n", LIS(n-1));      // with O(n^2) DP

  // 2020s problems will likely only accept O(n log k) solution
  // new limit: n can be up to 200K
  int k = 0, lis_end = 0;
  vi L(n, 0), L_id(n, 0);
  p.assign(n, -1);

  for (int i = 0; i < n; ++i) {                  // O(n)
    int pos = lower_bound(L.begin(), L.begin()+k, A[i]) - L.begin();
    L[pos] = A[i];                               // greedily overwrite this
    L_id[pos] = i;                               // remember the index too
    p[i] = pos ? L_id[pos-1] : -1;               // predecessor info
    if (pos == k) {                              // can extend LIS?
      k = pos+1;                                 // k = longer LIS by +1
      lis_end = i;                               // keep best ending i
    }

    printf("Considering element A[%d] = %d\n", i, A[i]);
    printf("LIS ending at A[%d] is of length %d: ", i, pos+1);
    printf("[");
    print_LIS(i);
    printf("]\n");
    print_array("L is now", L, k);
    printf("\n");
  }

  printf("Final LIS is of length %d: ", k);
  print_LIS(lis_end); printf("\n");

  assert(LIS(n-1) == k);                         // both must be identical
  return 0;
}
