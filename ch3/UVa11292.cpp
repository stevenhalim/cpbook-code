// The Dragon of Loowater

#include <bits/stdc++.h>
using namespace std;
 
#define MAX_nm 20010

int dragon[MAX_nm], knight[MAX_nm];
 
int main() {
  int n, m;
  while (scanf("%d %d", &n, &m), (n || m)) {
    int d, k;
    for (d = 0; d < n; d++) scanf("%d", &dragon[d]);
    sort(dragon, dragon+n);
    for (k = 0; k < m; k++) scanf("%d", &knight[k]);
    sort(knight, knight+m);
    int gold;
    gold = d = k = 0; // array dragon+knight are sorted in non decreasing order
    while (d < n && k < m) {              // still have dragon heads or knights
      while (k < m && dragon[d] > knight[k]) k++;   // find the required knight
      if (k == m) break;      // no knight can kill this dragon head, doomed :S
      gold += knight[k];                    // the king pay this amount of gold
      d++; k++;                           // next dragon head and knight please
    }
    if (d == n) printf("%d\n", gold);           // all dragon heads are chopped
    else        printf("Loowater is doomed!\n");
  }
  return 0;
}
