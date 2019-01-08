// Editing a Book

#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0, _n = (n); i < _n; i++)

typedef map<int, int> mii;

int encode(vector<int> &a) { // turn array into a number for efficiency
  int ret = 0;
  REP (i, a.size())
    ret = (ret * 10) + a[i];
  return ret;
}

// BFS from s until nL depth, store the state distance in "dis",
// "ref" is a state distance from another BFS source.
// If a node exists in "ref" then return the "meet in the middle distance"
//    from source s and from another source (ref's source)
int bfs(int s, int nL, mii &dis, mii &ref) {
  queue<int> q; q.push(s);
  dis.clear(); dis[s] = 0;
  for (int L = 0; L < nL && q.size(); L++) { // limit to depth nL only
    REP (qq, q.size()) { // we do not use while (!q.empty()) to ensure we only touch nL layers only
      int u = q.front(), t = u; q.pop();
      vector<int> a;
      REP (i, 9) a.push_back(t%10), t /= 10; // unpack the digits again
      reverse(a.begin(), a.end());
      for (int i = 0; i < 9; i++) { // try all possible substring
        for (int j = i; j < 9; j++) {
          vector<int> b = a;
          b.erase(b.begin()+i, b.begin()+j+1); // cut index [i..j]
          for (int k = 0; k < b.size(); k++) { // try all possible paste point
            vector<int> c = b;
            for (int l = j; l >= i; l--) // paste at location k (using array a)
              c.insert(c.begin()+k, a[l]);
            int v = encode(c);
            if (ref.count(v)) return L + 1 + ref[v]; // touching the other side, this is the answer: L + 1 (this move) + from v to sorted state
            if (dis.count(v)) continue; // if revisited, ignore
            // relax and push to queue again
            dis[v] = L+1;
            q.push(v);
          }
        }
      }
    }
  }
  return 5;	// maximum distance (upperbound)
}

int main() {
  mii d[10];
  int n, caseNo = 1;
  for (n = 1; n < 10; n++) { // precalculate bfs from 1, 12, 123, ..., 123456789
    int s = 0; REP(i, n) s = s * 10 + i + 1; // the source
    bfs(s, min(2, n), d[n], d[0]); // only need to go 2 level deep, d[0] is blank at this stage
  }
  while (scanf("%d", &n) != EOF && n) {
    vector<int> a(n);
    REP(i, n) scanf("%d", &a[i]); // up to n = 9, 1 digit, can be encoded as integer
    int v = encode(a), res;
    if (d[n].count(v)) res = d[n][v];	// search from s = 123456789, if found, we have an answer
    else               res = bfs(v, 2, d[0], d[n]);	// otherwise, search from target v (2 level deep), if still not found, answer = 5
    printf("Case %d: %d\n", caseNo++, res);
  }
  return 0;
}
