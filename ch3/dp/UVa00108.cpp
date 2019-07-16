// Maximum Sum
// O(n^3) 1D DP + greedy (Kadane's) solution, 0.000s in UVa

#include <bits/stdc++.h>
using namespace std;

#define MAX_n 110

int A[MAX_n][MAX_n];

int main() {
  int n; scanf("%d", &n);                        // square matrix size
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      scanf("%d", &A[i][j]);
      if (j > 0) A[i][j] += A[i][j-1];           // pre-processing
    }
  int maxSubRect = -127*100*100;                 // lowest possible val
  for (int l = 0; l < n; ++l)
    for (int r = l; r < n; ++r) {
      int subRect = 0;
      for (int row = 0; row < n; ++row) {
        // Max 1D Range Sum on columns of this row
        if (l > 0) subRect += A[row][r] - A[row][l-1];
        else       subRect += A[row][r];
        // Kadane's algorithm on rows
        if (subRect < 0) subRect = 0;            // restart if negative
        maxSubRect = max(maxSubRect, subRect);
      }
    }
  printf("%d\n", maxSubRect);
  return 0;
}



/*
// O(n^4) DP solution, ~0.076s in UVa
int main() {
  int n; scanf("%d", &n);                        // square matrix size
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      scanf("%d", &A[i][j]);
      if (i > 0) A[i][j] += A[i-1][j];           // add from top
      if (j > 0) A[i][j] += A[i][j-1];           // add from left
      if (i > 0 && j > 0) A[i][j] -= A[i-1][j-1];// avoid double count
    }                                            // inclusion-exclusion
  int maxSubRect = -127*100*100;                 // the lowest possible val
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)                  // start coordinate
      for (int k = i; k < n; ++k)
        for (int l = j; l < n; ++l) {            // end coord
          int subRect = A[k][l];                 // from (0, 0) to (k, l)
          if (i > 0) subRect -= A[i-1][l];       // O(1)
          if (j > 0) subRect -= A[k][j-1];       // O(1)
          if (i > 0 && j > 0) subRect += A[i-1][j-1]; // O(1)
          maxSubRect = max(maxSubRect, subRect); // the answer is here
        }
  printf("%d\n", maxSubRect);
  return 0;
}
*/



/*
// O(n^6) brute force solution, TLE (> 3s) in UVa
int main() {
  int n; scanf("%d", &n);                        // square matrix size
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      scanf("%d", &A[i][j]);
  int maxSubRect = -127*100*100;                 // the lowest possible val
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)                  // start coordinate
      for (int k = i; k < n; ++k)
        for (int l = j; l < n; ++l) {            // end coord
          int subRect = 0;                       // sum this sub-rectangle
          for (int a = i; a <= k; ++a)
            for (int b = j; b <= l; ++b)
              subRect += A[a][b];
          maxSubRect = max(maxSubRect, subRect); // the answer is here
        }
  printf("%d\n", maxSubRect);
  return 0;
}
*/
