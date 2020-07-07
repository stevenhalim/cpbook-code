// Distributing Ballot Boxes

#include <bits/stdc++.h>
using namespace std;

typedef tuple<double, int, int> dii;             // (ratio r, num, den)

int main() {
  int N, B;
  while (scanf("%d %d", &N, &B), (N != -1 && B != -1)) {
    priority_queue<dii> pq;                      // max pq
    for (int i = 0; i < N; ++i) {
      int a; scanf("%d", &a);
      pq.push({(double)a/1.0, a, 1});            // initially, 1 box/city
    }
    B -= N;                                      // remaining boxes
    while (B--) {                                // extra box->largest city
      auto [r, num, den] = pq.top(); pq.pop();   // current largest city
      pq.push({num/(den+1.0), num, den+1});      // reduce its workload
    }
    printf("%d\n", (int)ceil(get<0>(pq.top()))); // the final answer
  } // all other cities in the max pq will have equal or lesser ratio
  return 0;
}
