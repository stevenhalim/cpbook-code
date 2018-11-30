// UVa 11450 - Wedding Shopping - Bottom Up

#include <bits/stdc++.h>
using namespace std;

int g, money, k, TC, M, C;
int price[30][30];                       // price[g (<= 20)][model (<= 20)]
bool reachable[30][210];      // reachable table[g (<= 20)][money (<= 200)]

int main() {
  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &M, &C);
    for (g = 0; g < C; g++) {
      scanf("%d", &price[g][0]);   // store number of models in price[g][0]
      for (k = 1; k <= price[g][0]; k++)
        scanf("%d", &price[g][k]);
    }

    memset(reachable, false, sizeof reachable);         // clear everything
    // initial values (base cases), using first garment g = 0
    for (k = 1; k <= price[0][0]; k++) if (M-price[0][k] >= 0)
      reachable[0][M-price[0][k]] = true;

    for (g = 1; g < C; g++)                   // for each remaining garment
      for (money = 0; money < M; money++) if (reachable[g-1][money])
        for (k = 1; k <= price[g][0]; k++) if (money-price[g][k] >= 0)
          reachable[g][money-price[g][k]] = true;     // also reachable now

    for (money = 0; money <= M && !reachable[C-1][money]; money++);

    if (money == M+1) printf("no solution\n");    // last row has no on bit
    else              printf("%d\n", M-money);
  }
  return 0;
}


/*
// same as above, but using space saving trick

#include <bits/stc++.h>
using namespace std;

int g, money, k, TC, M, C, cur;
int price[30][30];
bool reachable[2][210];   // reachable table[ONLY TWO ROWS][money (<= 200)]

int main() {
  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &M, &C);
    for (g = 0; g < C; g++) {
      scanf("%d", &price[g][0]);
      for (k = 1; k <= price[g][0]; k++)
        scanf("%d", &price[g][k]);
    }

    memset(reachable, false, sizeof reachable);
    for (k = 1; k <= price[0][0]; k++) if (M-price[0][k] >= 0)
      reachable[0][M-price[0][k]] = true;
    cur = 1;                                      // we start with this row
    for (g = 1; g < C; g++) {
      memset(reachable[cur], false, sizeof reachable[cur]);    // reset row
      for (money = 0; money < M; money++) if (reachable[!cur][money])
        for (k = 1; k <= price[g][0]; k++) if (money-price[g][k] >= 0)
          reachable[cur][money-price[g][k]] = true;
      cur = !cur;                 // important technique: flip the two rows
    }

    for (money = 0; money <= M && !reachable[!cur][money]; money++);
    if (money == M+1) printf("no solution\n");    // last row has no on bit
    else              printf("%d\n", M-money);
} } // return 0;

*/
