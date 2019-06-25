// UVa 11450 - Wedding Shopping - Bottom Up (faster than Top Down)
#include <bits/stdc++.h>
using namespace std;

const int MAX_gm = 30; // up to 20 garments at most and 20 models/garment
const int MAX_M = 210; // maximum budget is 200

int price[MAX_gm][MAX_gm]; // price[g (<= 20)][k (<= 20)]
// bool reachable[MAX_gm][MAX_M]; // reachable table[g (<= 20)][money (<= 200)]
// if using space saving technique
bool reachable[2][MAX_M]; // reachable table[ONLY TWO ROWS][money (<= 200)]

int main() {
  int TC; scanf("%d", &TC);
  while (TC--) {
    int M, C; scanf("%d %d", &M, &C);
    for (int g = 0; g < C; ++g) {
      scanf("%d", &price[g][0]);                 // store k in price[g][0]
      for (int k = 1; k <= price[g][0]; ++k)
        scanf("%d", &price[g][k]);
    }

    memset(reachable, false, sizeof reachable);  // clear everything
    // initial values (base cases), using first garment g = 0
    for (int k = 1; k <= price[0][0]; ++k)
      if (M-price[0][k] >= 0)
        reachable[0][M-price[0][k]] = true;

    int money;
    // for (int g = 1; g < C; ++g)               // for each garment
    //   for (money = 0; money < M; money++) if (reachable[g-1][money])
    //     for (int k = 1; k <= price[g][0]; ++k) if (money-price[g][k] >= 0)
    //       reachable[g][money-price[g][k]] = true; // also reachable now
    // for (money = 0; money <= M && !reachable[C-1][money]; ++money);

    // then we modify the main loop in int main a bit
    int cur = 1;                                 // we start with this row
    for (int g = 1; g < C; ++g) {                // for each garment
      memset(reachable[cur], false, sizeof reachable[cur]); // reset row
      for (money = 0; money < M; ++money) if (reachable[!cur][money])
        for (int k = 1; k <= price[g][0]; ++k) if (money-price[g][k] >= 0)
          reachable[cur][money-price[g][k]] = true;
      cur = 1-cur;                               // flip the two rows
    }
    for (money = 0; money <= M && !reachable[!cur][money]; ++money);

    if (money == M+1) printf("no solution\n");   // last row has no on bit
    else              printf("%d\n", M-money);
  }
  return 0;
}
