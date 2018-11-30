#include <bits/stdc++.h>
using namespace std;

typedef tuple<int, int, int> iii;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

// Union-Find Disjoint Sets Library written in OOP manner, using both path compression and union by rank heuristics
class UnionFind {                                              // OOP style
private:
  vi p, rank, setSize;                       // remember: vi is vector<int>
  int numSets;
public:
  UnionFind(int N) {
    setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
    p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) {
    if (!isSameSet(i, j)) { numSets--;
      int x = findSet(i), y = findSet(j);
      // rank is used to keep the tree short
      if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
      else                   { p[x] = y; setSize[y] += setSize[x];
                               if (rank[x] == rank[y]) rank[y]++; } } }
  int numDisjointSets() { return numSets; }
  int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

vector<vii> AL;      // for Prim's, we need the graph to be stored in an AL
vi taken;                             // global boolean flag to avoid cycle
priority_queue<ii> pq;       // priority queue to help choose shorter edges
          // note: default setting for C++ STL priority_queue is a max heap
void process(int u) {      // so, we use -ve sign to reverse the sort order
  taken[u] = 1;
  for (auto &v : AL[u])
    if (!taken[v.first])
      pq.push({-v.second, -v.first});
}                                  // sort by (inc) weight then by (inc) id

int main() {
  /*
  // Graph in Figure 4.10 left, format: list of weighted edges
  // This example shows another form of reading graph input
  5 7
  0 1 4
  0 2 4
  0 3 6
  0 4 6
  1 2 2
  2 3 8
  3 4 9
  */

  freopen("07_in.txt", "r", stdin);

  int V, E; scanf("%d %d", &V, &E);
  // Kruskal's algorithm merged with Prim's algorithm
  AL.assign(V, vii());
  vector<iii> EL;                          // (weight and two end vertices)
  for (int i = 0; i < E; i++) {
    int u, v, w; scanf("%d %d %d", &u, &v, &w);           // read (u, v, w)
    EL.emplace_back(w, u, v);
    AL[u].emplace_back(v, w);
    AL[v].emplace_back(u, w);
  }
  sort(EL.begin(), EL.end());             // sort by edge weight O(E log E)
                      // note: pair object has built-in comparison function

  int mst_cost = 0, num_taken = 0;
  UnionFind UF(V);                     // all V are disjoint sets initially
  for (int i = 0; i < E && num_taken < V-1; i++) {   // for each edge, O(E)
    int w, u, v; tie(w, u, v) = EL[i];
    if (!UF.isSameSet(u, v)) {                                     // check
      num_taken++;             // one more edge is taken as part of the MST
      mst_cost += w;                          // add the weight of e to MST
      UF.unionSet(u, v);                                       // link them
  } }                       // note: the runtime cost of UFDS is very light
  // note: the number of disjoint sets must eventually be 1 for a valid MST
  printf("MST cost = %d (Kruskal's)\n", mst_cost);

// inside int main() --- assume the graph is stored in AdjList, pq is empty
  taken.assign(V, 0);                // no vertex is taken at the beginning
  process(0);   // take vertex 0 and process all edges incident to vertex 0
  mst_cost = 0; num_taken = 0;      // no edge has been taken at this point
  while (!pq.empty() && num_taken < V-1) {     // until V-1 edges are taken
    int w, u; tie(w, u) = pq.top(); pq.pop();
    w = -w; u = -u;                             // negate the id and weight
    if (!taken[u]) {               // we have not connected this vertex yet
      num_taken++;             // one more edge is taken as part of the MST
      mst_cost += w;                  // add the weight of this edge to MST
      process(u);                // take u, process all edges incident to u
  } }                                      // each edge is in pq only once!
  printf("MST cost = %d (Prim's)\n", mst_cost);

  return 0;
}
