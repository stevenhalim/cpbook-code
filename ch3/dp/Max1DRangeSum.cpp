#include <bits/stdc++.h>
using namespace std;

int main() {
  int n = 9, A[] = { 4,-5, 4,-3, 4, 4,-4, 4,-5 };// a sample array A
  int sum = 0, ans = 0;
  for (int i = 0; i < n; ++i) {                  // linear scan, O(n)
    sum += A[i];                                 // greedily extend this
    ans = max(ans, sum);                         // keep the cur max RSQ
    if (sum < 0) sum = 0;                        // reset the running sum
  }                                              // if it ever dips below 0
  // rationale: starting from 0 is better for future
  // iterations than starting from -ve running sum
  printf("Max 1D Range Sum = %d\n", ans);        // should be 9
  return 0;
}
