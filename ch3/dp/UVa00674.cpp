// Coin Change

#include <bits/stdc++.h>
using namespace std;

int N = 5, V, coinValue[5] = {1, 5, 10, 25, 50}, memo[6][7500];
// N and coinValue are fixed for this problem, max V is 7489

int ways(int type, int value) {
  if (value == 0) return 1;                      // one way, use nothing
  if ((value < 0) || (type == N)) return 0;      // invalid or done
  int &ans = memo[type][value];
  if (ans != -1) return ans;                     // was computed before
  return ans = ways(type+1, value) +             // ignore this type
               ways(type, value-coinValue[type]);// one more of this type
}

int main() {
  memset(memo, -1, sizeof memo); // we only need to initialize this once
  while (scanf("%d", &V) != EOF)
    printf("%d\n", ways(0, V));
  return 0;
}
