/* UVa 10003
   
   O(N^2) with Knuth-Yao dp optimization

   Bottom-up implementation
*/
#include <bits/stdc++.h>
using namespace std;

int l, n;
int A[55];
int cut[55][55];
int opt[55][55];

int main() {
  while (scanf("%d", &l), l) {
    A[0] = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &A[i]);
    A[n+1] = l;
    
    for ( int i = 0; i < n+2; ++i )
      for ( int j = 0; j < n+2; ++j )
        cut[i][j] = 1e9;
    for ( int i = 1; i < n+3; ++i ) {
      cut[i-1][i] = 0;
      opt[i-1][i] = i;
    }
    for ( int i = n+1; i >= 0; --i )
      for ( int j = i; j < n+2; ++j )
        for ( int k = opt[i][j-1]; k <= opt[i+1][j]; ++k ) {
          int value = cut[i][k]+cut[k][j]+A[j]-A[i];
          if ( value < cut[i][j] ) {
            cut[i][j] = value;
            opt[i][j] = k;
          }
        }

    printf("The minimum cutting is %d.\n", cut[0][n+1]);
  }
  return 0;
}
