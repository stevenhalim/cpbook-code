#include <bits/stdc++.h>                         // C++ code for task 8
using namespace std;
#define LSOne(S) ((S) & -(S))                    // notice the brackets
int main() {
  int N = 4;                                     // change 4 to 20 to match the actual problem (but it will take some time to print)
  for (int i = 0; i < (1<<N); ++i) {
    int pos = i;
    while (pos) {
      int ls = LSOne(pos);
      printf("%d ", __builtin_ctz(ls)+1);        // this idx is part of set
      pos -= ls;
    }
    printf("\n");
  }
}
