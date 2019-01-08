// Free Parentheses

#include <bits/stdc++.h>
using namespace std;

int num[35], sign[35], cnt;
int memo[35][35][6500];
set<int> S;

void dp(int open, int n, int value) {
  if (memo[open][n][value+3200] != -1) return;
  if (n == cnt-1) {
    S.insert(value);
    return;
  }
  int nval = sign[n+1] * num[n+1] * (open%2 == 0 ? 1 : -1);
  if (open > 0) dp(open-1, n+1, value+nval);
  if (sign[n+1] == -1) dp(open+1, n+1, value+nval);
  dp(open, n+1, value+nval);
  memo[open][n][value+3200] = 0;
}

int main() {
  string s;
  char c;
  while (getline(cin, s)) {
    stringstream sin;
    sin << s;
    sin >> num[0];
    S.clear();
    sign[0] = 1;
    cnt = 1;
    while (sin >> c) {
      sign[cnt] = c == '-' ? -1 : 1;
      sin >> num[cnt];
      cnt++;
    }
    memset(memo, -1, sizeof memo);
    dp(0, 0, num[0]);
    printf("%d\n", (int)S.size());
  }
  return 0;
}
