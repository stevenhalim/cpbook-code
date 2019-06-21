// Beverages

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main() {
  int caseNo = 1;
  while (1) {
    char line[1000]; gets(line);
    if (feof(stdin)) break;

    int N; sscanf(line, "%d", &N);
    vector<vi> AL;
    map<string, int> mapper;
    map<int, string> reverseMapper;
    for (int i = 0; i < N; ++i) {
      char B1[60]; gets(B1);
      mapper[(string)B1] = i; // give index to this
      reverseMapper[i] = (string)B1;
      vector<int> Neighbor;
      AL.push_back(Neighbor);
    }

    int in_degree[110]; memset(in_degree, 0, sizeof in_degree);
    int M; sscanf(gets(line), "%d", &M);
    for (int i = 0; i < M; ++i) {
      char B1[60], B2[60]; sscanf(gets(line), "%s %s", &B1, &B2);
      int a = mapper[(string)B1];
      int b = mapper[(string)B2];
      AL[a].push_back(b);
      ++in_degree[b];
    }

    printf("Case #%d: Dilbert should drink beverages in this order:", caseNo++);

    // enqueue vertices with zero incoming degree into a (priority) queue pq
    priority_queue<int, vi, greater<int>> pq;    // min priority queue
    for (int u = 0; u < N; ++u)
      if (in_degree[u] == 0) // all vertices with 0 in-degree can be processed
        pq.push(u);                              // smaller index goes first

    while (!pq.empty()) {                        // Kahn's algorithm
      int u = pq.top(); pq.pop();
      printf(" %s", reverseMapper[u].c_str());
      for (auto &v : AL[u]) {                    // process u
        --in_degree[v];                          // virtually 'remove' u->v
        if (in_degree[v] == 0)                   // v is the next candidate
          pq.push(v);                            // smallest id to front
      }
    }

    printf(".\n\n");
    gets(line); // dummy
  }
  return 0;
}
