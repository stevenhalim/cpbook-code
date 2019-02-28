#include <bits/stdc++.h>                         // C++ code for task 8
using namespace std;
#define LSOne(S) (S & (-S))
int main() {
  int N = 20;
  for (int i = 0; i < (1<<N); ++i) {
    int pos = i;
    while (pos) {
      int ls = LSOne(pos);
      pos -= ls;
      printf("%d ", __builtin_ctz(ls));          // this idx is part of set
    }
    printf("\n");
  }
}
