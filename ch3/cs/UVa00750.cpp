#include <bits/stdc++.h>
using namespace std;

int row[8], a, b, lineCounter;                   // global variables

bool canPlace(int r, int c) {
  for (int prev = 0; prev < c; ++prev)           // check previous Queens
    if ((row[prev] == r) || (abs(row[prev]-r) == abs(prev-c)))
      return false;                              // infeasible
  return true;
}

void backtrack(int c) {
  if ((c == 8) && (row[b] == a)) {               // a candidate sol
    printf("%2d      %d", ++lineCounter, row[0]+1);
    for (int j = 1; j < 8; ++j) printf(" %d", row[j]+1);
    printf("\n");
    return;                                      // optional statement
  }
  for (int r = 0; r < 8; ++r) {                  // try all possible row
    if ((c == b) && (r != a)) continue;          // early pruning
    if (canPlace(r, c))                          // can place a Queen here?
      row[c] = r, backtrack(c+1);                // put here and recurse
  }
}

int main() {
  int TC; scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &a, &b); --a; --b;            // to 0-based indexing
    memset(row, 0, sizeof row); lineCounter = 0;
    printf("SOLN       COLUMN\n");
    printf(" #      1 2 3 4 5 6 7 8\n\n");
    backtrack(0);                                // sub 8! operations
    if (TC) printf("\n");
  }
  return 0;
}
