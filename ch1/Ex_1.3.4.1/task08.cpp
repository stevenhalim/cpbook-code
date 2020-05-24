#include <bits/stdc++.h>                         // C++ code for task 8
using namespace std;
#define LSOne(S) ((S) & -(S))                    // notice the brackets
int main() {
  int N = 20;
  for (int i = 0; i < (1<<N); ++i) {
    int pos = i;
    while (pos) {
      int ls = LSOne(pos);
      printf("%d ", __builtin_ctz(ls));          // this idx is part of set
      pos -= ls;
    }
    printf("\n");
  }
}
