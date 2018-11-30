// Pseudo-Random Numbers

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;

int Z, I, M, L;

int f(int x) { return (Z*x + I) % M; }

ii floydCycleFinding(int x0) {  // function int f(int x) is defined earlier
  // 1st part: finding k*mu, hare's speed is 2x tortoise's
  int tortoise = f(x0), hare = f(f(x0));    // f(x0) is the node next to x0
  while (tortoise != hare) { tortoise = f(tortoise); hare = f(f(hare)); }
  // 2nd part: finding mu, hare and tortoise move at the same speed
  int mu = 0; hare = x0;
  while (tortoise != hare) { tortoise = f(tortoise); hare = f(hare); mu++; }
  // 3rd part: finding lambda, hare moves, tortoise stays
  int lambda = 1; hare = f(tortoise);
  while (tortoise != hare) { hare = f(hare); lambda++; }
  return ii(mu, lambda);
}

int main() {
  int caseNo = 1;
  while (scanf("%d %d %d %d", &Z, &I, &M, &L), (Z || I || M || L)) {
    ii result = floydCycleFinding(L);
    printf("Case %d: %d\n", caseNo++, result.second);
  }
  return 0;
}
