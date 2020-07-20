#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

vi match, vis;                                   // global variables
vector<vi> AL;

int Aug(int L) {
  if (vis[L]) return 0;                          // L visited, return 0
  vis[L] = 1;
  for (auto &R : AL[L])
    if ((match[R] == -1) || Aug(match[R])) {
      match[R] = L;                              // flip status
      return 1;                                  // found 1 matching
    }
  return 0;                                      // no matching
}

bool isprime(int v) {
  int primes[10] = {2,3,5,7,11,13,17,19,23,29};
  for (int i = 0; i < 10; ++i)
    if (primes[i] == v)
      return true;
  return false;
}

int main() {
// inside int main()
  // build bipartite graph with directed edge from left to right set

/*
  // Graph in Figure 4.40 can be built on the fly
  // we know there are 6 vertices in this bipartite graph, left side are numbered 0,1,2, right side 3,4,5
  int V = 6, Vleft = 3, set1[3] = {1,7,11}, set2[3] = {4,10,12};

  // Graph in Figure 4.41 can be built on the fly
  // we know there are 5 vertices in this bipartite graph, left side are numbered 0,1, right side 3,4,5
  //int V = 5, Vleft = 2, set1[2] = {1,7}, set2[3] = {4,10,12};

  // build the bipartite graph, only directed edge from left to right is needed
  AL.assign(V, vi());
  for (int i = 0; i < Vleft; ++i)
    for (int j = 0; j < 3; ++j)
      if (isprime(set1[i] + set2[j]))
        AL[i].push_back(3 + j);
*/

  // For bipartite graph in Figure 4.44, V = 5, Vleft = 3 (vertex 0 unused)
  // AL[0] = {} // dummy vertex, but you can choose to use this vertex
  // AL[1] = {3, 4}
  // AL[2] = {3}
  // AL[3] = {}   // we use directed edges from left to right set only
  // AL[4] = {}

  int V = 5, Vleft = 3;                          // we ignore vertex 0
  AL.assign(V, {});
  AL[1] = {3, 4};
  AL[2] = {3};

  unordered_set<int> freeV;
  for (int L = 0; L < Vleft; ++L)
    freeV.insert(L);                             // initial assumption
  match.assign(V, -1);
  int MCBM = 0;
  // Greedy pre-processing for trivial Augmenting Paths
  // try commenting versus un-commenting this for-loop
  for (int L = 0; L < Vleft; ++L) {              // O(V+E)
    vi candidates;
    for (auto &R : AL[L])
      if (match[R] == -1)
        candidates.push_back(R);
    if ((int)candidates.size() > 0) {
      ++MCBM;
      freeV.erase(L);                            // L is matched
      int a = rand()%(int)candidates.size();     // randomize this
      match[candidates[a]] = L;
    }
  }                                              // for each free vertex
  for (auto &f : freeV) {                        // (in random order)
    vis.assign(Vleft, 0);                        // reset first
    MCBM += Aug(f);                              // try to match f
  }
  cout << "Found " << MCBM << " matchings\n";    // the answer is 2 for Figure 4.38

  return 0;
}
