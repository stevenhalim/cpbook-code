// This code uses new C++17 structured binding
// use this compiler setting "g++ -O2 -std=gnu++17 {cpp17file}"

// Disclaimer: This code is a hybrid between old CP1-2-3 implementation of
// Edmonds Karp's algorithm -- re-written in OOP fashion and the fast
// Dinic's algorithm implementation by
// https://github.com/jaehyunp/stanfordacm/blob/master/code/Dinic.cc
// This code is written in modern C++17 standard

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18; // INF = 1e18, not 2^63-1 to avoid overflow

class max_flow {
protected:
  int V;
  vector<edge> EL;
  vector<vi> AL;
  vi d, last;
  vector<ii> p;

  bool BFS(int s, int t) { // BFS to find augmenting path in residual graph
    d.assign(V, -1); d[s] = 0;
    queue<int> q({s});
    p.assign(V, {-1, -1});                       // record BFS sp tree
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == t) break;                         // stop as sink t reached
      for (auto &idx : AL[u]) {                  // explore neighbors of u
        auto &[also_u, v, cap, flow] = EL[idx];  // stored in EL[idx]
        if ((cap-flow > 0) && (d[v] == -1))      // positive residual edge
          d[v] = d[u]+1, q.push(v), p[v] = {u, idx}; // 3 lines in one!
      }
    }
    return d[t] != -1;                           // has an augmenting path
  }

  ll send_one_flow(int s, int t, ll f = INF) {   // send one flow from s->t
    if (s == t) return f;                        // bottleneck edge f found
    auto &[u, idx] = p[t];
    auto &[also_u, v, cap, flow] = EL[idx];
    ll pushed = send_one_flow(s, u, min(f, cap-flow));
    flow += pushed;
    auto &[ru, rv, rcap, rflow] = EL[idx^1];     // back edge
    rflow -= pushed;                             // back flow
    return pushed;
  }

  ll DFS(int s, int t, ll f = INF) {             // traverse from s->t
    if ((s == t) || (f == 0)) return f;
    for (int &i = last[s]; i < AL[s].size(); ++i) { // remember last edge
      auto &[u, v, cap, flow] = EL[AL[s][i]];
      if (d[v] == d[u]+1) {                      // in current layer graph
        if (ll pushed = DFS(v, t, min(f, cap-flow))) {
          flow += pushed;
          auto &[ru, rv, rcap, rflow] = EL[AL[s][i]^1]; // back edge
          rflow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }

public:
  max_flow(int _V) : V(_V) {
    EL.clear();
    AL.assign(V, vi());
  }

  // if you are adding a bidirectional edge u<->v with weight w into your
  // flow graph, set directed = false (default value is directed = true)
  void add_edge(int u, int v, ll w, bool directed = true) {
    if (u == v) return;                          // safeguard: no self loop
    EL.emplace_back(u, v, w, 0);                 // u->v, cap w, flow 0
    AL[u].push_back(EL.size()-1);                // remember this index
    EL.emplace_back(v, u, directed ? 0 : w, 0);  // back edge
    AL[v].push_back(EL.size()-1);                // remember this index
  }

  ll edmonds_karp(int s, int t) {
    ll mf = 0;                                   // mf stands for max_flow
    while (BFS(s, t)) {                          // an O(VE^2) EK algorithm
      ll f = send_one_flow(s, t);                // find and send 1 flow f
      if (f == 0) break;                         // if f == 0, stop
      mf += f;                                   // if f > 0, add to mf
    }
    return mf;
  }

  ll dinic(int s, int t) {
    ll mf = 0;                                   // mf stands for max_flow
    while (BFS(s, t)) {                          // an O(VE^2) EK algorithm
      last.assign(V, 0);                         // important speedup
      while (ll f = DFS(s, t))                   // exhaust blocking flow
        mf += f;
    }
    return mf;
  }
};

class max_flow_with_VW : public max_flow {
private: 
  inline int getIn(int v) { return (v << 1); }
  inline int getOut(int v) { return (v << 1) + 1; }

public:
  max_flow_with_VW(int _V) : max_flow(2 * _V) {
    for (int i = 0; i < _V; i++) 
      max_flow::add_edge(getIn(i), getOut(i), INF);              // All vertices are initialised with infinite capacity
  }

  void add_vertex_weight(int v, ll w) {
    get<2>(EL[getIn(v)]) = w;
  }

  void add_edge(int u, int v, ll w, bool directed = true) {
    max_flow::add_edge(getOut(u), getIn(v), w);
    if (!directed) max_flow::add_edge(getOut(v), getIn(u), w);
  }

  ll edmonds_karp(int s, int t) {
    return max_flow::edmonds_karp(getIn(s), getOut(t));
  }

  ll dinic(int s, int t) {
    return max_flow::dinic(getIn(s), getOut(t));
  }
};

int main() {
  /*
  // Graph in Figure 4.24
  4 0 3
  2 2 3 1 7
  2 2 1 3 2
  1 3 7
  0
  */

  freopen("maxflow_in.txt", "r", stdin);

  int V, s, t; scanf("%d %d %d", &V, &s, &t);
  max_flow mf(V);
  for (int u = 0; u < V; ++u) {
    int k; scanf("%d", &k);
    while (k--) {
      int v, w; scanf("%d %d", &v, &w);
      mf.add_edge(u, v, w);                      // default: directed edge
    }
  }

  // printf("%lld\n", mf.edmonds_karp(s, t));
  printf("%lld\n", mf.dinic(s, t));

  printf("=====\n");

  /*
  // Sample graph with vertex capacities (source and sink have infinite capacities) 
  5 0 4
  5 6 7
  2 1 5 2 3
  1 3 10
  1 3 4
  1 4 10
  0
  */

  scanf("%d %d %d", &V, &s, &t);
  max_flow_with_VW mfvw(V);
  for (int u = 1; u < V - 1; ++u) {
    int w; scanf("%d", &w);
    mfvw.add_vertex_weight(u, w);
  }
  for (int u = 0; u < V; ++u) {
    int k; scanf("%d", &k);
    while (k--) {
      int v, w; scanf("%d %d", &v, &w);
      mfvw.add_edge(u, v, w);                      
    }
  }

  // printf("%lld\n", mfvw.edmonds_karp(s, t));
  printf("%lld\n", mfvw.dinic(s, t));

  return 0;
}
