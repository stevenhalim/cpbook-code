#include <bits/stdc++.h>                         // C++ code for task 4
using namespace std;
#define ALL(x) x.begin(), x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
int main() {
  vector<int> v = {1, 2, 2, 2, 3, 3, 2, 2, 1};
  sort(ALL(v)); UNIQUE(v);
  for (auto &x : v) printf("%d\n", x);
}
