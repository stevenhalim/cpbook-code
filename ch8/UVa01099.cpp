// Sharing Chocolate

#include <bits/stdc++.h>
using namespace std;

#define twoPow(X) (1 << (X))
#define bitOn(S, X) (((S) & twoPow(X)) != 0)
#define setBitOn(S, X) ((S) | twoPow(X))
#define getBit(S, X) (((S) >> X) & 1)

int i, n, target, x, y, num_pieces[16], caseNo = 0;
int memo[101][1<<16], area[1<<16];

int count_area(int S) {
  int retval = 0;
  for (int i = 0; i < n; i++)
    if (bitOn(S, i)) // if this bit is on
      retval += num_pieces[i];
  return retval;
}

bool dp(int w, int h, int S) {
  if (memo[w][S] != -1) return memo[w][S];       // note: h is not memo-ed
  int a = area[S];
  if ((w == 0) || (a%w != 0)) return memo[w][S] = false;
  // if (memo[h][S] != -1) return memo[w][S] = memo[h][S];
  vector<short> bit;
  for (int i = 0; i < n; ++i)
    if (bitOn(S, i))
      bit.push_back(i);
  int l = (int)bit.size();
  if (l == 1) // if only one item
    memo[w][S] = true;
  else {
    memo[w][S] = false;
    for (int t = 0; t <= twoPow(l-1)-2; ++t) {
      int s1 = setBitOn(0, bit[l-1]); // Set one always belong to set #1, can reduce search space by half
      int s2 = 0;
      for (int k = 0; k < l-1; ++k)
        if (bitOn(t, k))
          s1 = setBitOn(s1, bit[k]);
        else
          s2 = setBitOn(s2, bit[k]);
      bool op1 = dp(w, area[s1]/w, s1) && dp(w, area[s2]/w, s2); // horizontal cut
      bool op2 = dp(h, area[s1]/h, s1) && dp(h, area[s2]/h, s2); // vertical cut
      if (op1 || op2) {
        memo[w][S] = true;
        break;
      } 
    }     
  }
  return memo[w][S];
}

int main() {
  while (scanf("%d", &n), n) {
    scanf("%d %d", &x, &y);
    for (i = 0; i < n; ++i) scanf("%d", &num_pieces[i]);
    target = twoPow(n)-1;
    memset(area, -1, sizeof area);
    for (i = 0; i <= target; ++i) area[i] = count_area(i); // O(32,768*16 = 524,288)
    memset(memo, -1, sizeof memo);
    printf("Case %d: %s", ++caseNo, (area[target] != x*y || // special case: cannot
                                     !(dp(y, x, target))) ? "No\n" : "Yes\n"); // try subproblems
  }
  return 0;
}
