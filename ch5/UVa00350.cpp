// Pseudo-Random Numbers

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

int Z, I, M;

int f(int x) { return (Z*x + I) % M; }

ii floydCycleFinding(int x0) {                   // f(x) is defined above
  // 1st part: finding k*mu, hare h's speed is 2x tortoise t's
  int t = f(x0), h = f(f(x0));                   // f(x0) is after x0
  while (t != h) { t = f(t); h = f(f(h)); }
  // 2nd part: finding mu, hare h and tortoise t move at the same speed
  int mu = 0; h = x0;
  while (t != h) { t = f(t); h = f(h); ++mu; }
  // 3rd part: finding lambda, hare h moves, tortoise t stays
  int lambda = 1; h = f(t);
  while (t != h) { h = f(h); ++lambda; }
  return {mu, lambda};
}

int main() {
  freopen("in.txt", "r", stdin);
  int caseNo = 0, L;
  while (scanf("%d %d %d %d", &Z, &I, &M, &L), (Z || I || M || L)) {
    auto [mu, lambda] = floydCycleFinding(L);
    printf("Case %d: %d\n", ++caseNo, lambda);
    return 0;
  }
  return 0;
}
