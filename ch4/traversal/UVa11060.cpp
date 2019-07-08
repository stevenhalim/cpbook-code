// Beverages

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main() {
  int caseNo = 0;
  while (1) {
    char line[1000]; gets(line);
    if (feof(stdin)) break;

    int N; sscanf(line, "%d", &N);
    vector<vi> AL(N, vi());
    unordered_map<string, int> mapper;
    unordered_map<int, string> reverseMapper;
    for (int i = 0; i < N; ++i) {
      char B1[60]; gets(B1);
      mapper[(string)B1] = i;                    // give index i to B1
      reverseMapper[i] = (string)B1;
    }

    vi in_degree(N, 0);
    int M; sscanf(gets(line), "%d", &M);
    for (int i = 0; i < M; ++i) {
      char B1[60], B2[60]; sscanf(gets(line), "%s %s", &B1, &B2);
      int a = mapper[(string)B1], b = mapper[(string)B2];
      AL[a].push_back(b);                        // directed edge
      ++in_degree[b];
    }

    printf("Case #%d: Dilbert should drink beverages in this order:", ++caseNo);

    // enqueue vertices with zero incoming degree into a (priority) queue pq
    priority_queue<int, vi, greater<int>> pq;    // min priority queue
    for (int u = 0; u < N; ++u)
      if (in_degree[u] == 0)                     // next to be processed
        pq.push(u);                              // smaller index first

    while (!pq.empty()) {                        // Kahn's algorithm
      int u = pq.top(); pq.pop();
      printf(" %s", reverseMapper[u].c_str());   // process u here
      for (auto &v : AL[u]) {
        --in_degree[v];                          // virtually remove u->v
        if (in_degree[v] > 0) continue;          // not a candidate, skip
        pq.push(v);                              // enqueue v in pq
      }
    }

    printf(".\n\n");
    gets(line); // dummy
  }
  return 0;
}
