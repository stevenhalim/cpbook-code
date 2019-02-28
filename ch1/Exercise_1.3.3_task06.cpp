#include <bits/stdc++.h>                         // C++ code for task 6
using namespace std;
int main() {
  int n = 5, L[] = {10, 7, 5, 20, 8}, v = 7;
  sort(L, L+n);
  printf("%d\n", binary_search(L, L+n, v));      // should be index 1
}
