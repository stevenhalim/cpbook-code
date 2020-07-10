// Free Parentheses

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 35;
const int OFFSET = 3000;

int num[MAX_N], sign[MAX_N];
int N;
bool visited[MAX_N][MAX_N][6010];
unordered_set<int> S;

void dp(int idx, int open, int val) {            // OFFSET = 3000
  if (visited[idx][open][val+OFFSET])            // has been reached before
    return;                                      // +3000 offset to make
                                                 // indices in [100..6000]
  visited[idx][open][val+OFFSET] = true;         // set this to true
  if (idx == N) {                                // last number
    S.insert(val);                               // val is one
    return;                                      // of expression result
  }
  int nval = val + num[idx] * sign[idx] * ((open%2 == 0) ? 1 : -1);
  if (sign[idx] == -1)                           // 1: put open bracket
    dp(idx+1, open+1, nval);                     //    only if sign is -
  if (open > 0)                                  // 2: put close bracket
    dp(idx+1, open-1, nval);                     //    if we have >1 opens
  dp(idx+1, open, nval);                         // 3: do nothing
}

int main() {
  string s;
  while (getline(cin, s)) {
    stringstream sin(s);
    sign[0] = 1;
    sin >> num[0];
    N = 1;
    S.clear();
    char c;
    while (sin >> c) {
      sign[N] = (c == '-' ? -1 : 1);
      sin >> num[N];
      ++N;
    }
    memset(visited, false, sizeof visited);
    dp(0, 0, num[0]);
    printf("%d\n", (int)S.size());
  }
  return 0;
}
