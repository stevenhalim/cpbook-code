// Gentlemen Agreement

#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for (int i=(a),_b=(b); i>=_b; i--)
#define REP(i,n) for (int i=0,_n=(n); i<_n; i++)
#define MAXI 62

long long AM[MAXI], dpcon[MAXI];
int V, E, nS, mxS;

void backtracking(int i, long long used, int depth) {
  if (used == (1<<V)-1) {                 // all intersections are visited
    nS++;                                         // one more possible set
    mxS = max(mxS, depth);                              // size of the set
  }
  else {
    for (int j = i; j < V; j++)
      if (!(used & (1<<j)))           // if intersection i is not yet used
        backtracking(j+1, used|AM[j], depth+1); // use i and its neighbors
  }
}

int main() {
  int TC; scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &V, &E);

    // a more powerful, bit-wise adjacency list (for faster set operations)
    for (int i = 0; i < V; i++)
      AM[i] = (1 << i);                                  // i to itself
    for (int i = 0; i < E; i++) {
      int a, b; scanf("%d %d", &a, &b);
      AM[a] |= (1<<b);
      AM[b] |= (1<<a);
    }

    // speed up
    dpcon[V] = 0;
    FORD (i, V-1, 0) dpcon[i] = AM[i] | dpcon[i + 1];

    nS = mxS = 0;
    backtracking(0, 0, 0); // just a backtracking with bitmask/subset
    printf("%d\n%d\n", nS, mxS);
  }
  return 0;
}
