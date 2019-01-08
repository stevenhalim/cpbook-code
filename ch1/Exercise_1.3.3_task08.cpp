#include <bits/stdc++.h>                             // C++ code for task 8
using namespace std;
#define LSOne(S) (S & (-S))
int main() {
  int p[20], N = 20, pos, ls;
  for (int i = 0; i < N; i++) p[i] = i;
  for (int i = 0; i < (1<<N); i++) {
    pos = i;
    while (pos) {
      ls = LSOne(pos);
      pos -= ls;
      printf("%d ", __builtin_ctz(ls)); }      // this index is part of set
    printf("\n");
} }
