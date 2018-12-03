#include <bits/stdc++.h>
using namespace std;

#define MAXN 10000                           // adjust this value as needed
#define L2_N 14        // 2^14 = 16384 > 10000, adjust this value as needed

class RMQ {                                          // Range Minimum Query
private:
  int i, j, k, x, y, P2[L2_N], L2[(1<<L2_N)+10], _A[MAXN], SpT[L2_N][MAXN];
public:
  RMQ(int n, int A[]) {    // constructor as well as pre-processing routine
    // speed up powers of 2 and logarithmic computations
    memset(L2, 0, sizeof L2);
    for (i = 0; i <= L2_N; i++) {
      P2[i] = (1<<i);
      L2[(1<<i)] = i;
    }
    L2[0] = L2[1] = 0;
    for (i = 2; i < (1<<L2_N); i++)
      if (L2[i] == 0)
        L2[i] = L2[i-1];

    // initialization
    for (j = 0; j < n; j++) {
      _A[j] = A[j];
      SpT[0][j] = j;                             // RMQ of sub array [j..j]
    }

    // the two nested loops below have overall time complexity = O(n log n)
    for (i = 1; (1<<i) <= n; i++)     // for each i s.t. 2^i <= n, O(log n)
      for (j = 0; j+(1<<i)-1 < n; j++) {          // for each valid j, O(n)
        x = SpT[i-1][j];                             // covers [j..j+2^i-1]
        y = SpT[i-1][j+(1<<(i-1))];      // covers [j+(1<<(i-1))..j+(1<<i)]
        SpT[i][j] = _A[x] <= _A[y] ? x : y;
      }
  }

  int query(int i, int j) {
    k = L2[j-i+1];                                        // 2^k <= (j-i+1)
    x = SpT[k][i];                                   // covers [i..i+2^k-1]
    y = SpT[k][j-P2[k]+1];                           // covers [j-2^k+1..j]
    // printf("%k = %d, i = %d, modj = %d, x = %d, y = %d\n", k, i, j-P2[k]+1, x, y);
    return _A[x] <= _A[y] ? x : y;
  }
};

int main() {
  // same example as in chapter 2: segment tree
  int n = 7, A[] = {18, 17, 13, 19, 15, 11, 20};
  RMQ rmq(n, A);
  // for (int i = 0; i < n; i++)
  //   for (int j = i; j < n; j++)
  //     printf("RMQ(%d, %d) = %d\n", i, j, rmq.query(i, j));
  printf("%d\n", rmq.query(1, 5));

  return 0;
}
