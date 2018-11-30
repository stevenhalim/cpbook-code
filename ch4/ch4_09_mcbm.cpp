#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

vector<vi> AdjList;
vi match, vis;                                          // global variables

int Aug(int L) {                 // return 1 if an augmenting path is found
  if (vis[L]) return 0;                               // return 0 otherwise
  vis[L] = 1;
  for (auto &R : AdjList[L])
    if (match[R] == -1 || Aug(match[R])) {
      match[R] = L; return 1;                           // found 1 matching
    }
  return 0;                                                  // no matching
}

bool isprime(int v) {
  int primes[10] = {2,3,5,7,11,13,17,19,23,29};
  for (int i = 0; i < 10; i++)
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
  AdjList.assign(V, vi());
  for (int i = 0; i < Vleft; i++)
    for (int j = 0; j < 3; j++)
      if (isprime(set1[i] + set2[j]))
        AdjList[i].push_back(3 + j);
*/

  // For bipartite graph in Figure 4.44, V = 5, Vleft = 3 (vertex 0 unused)
  // AdjList[0] = {} // dummy vertex, but you can choose to use this vertex
  // AdjList[1] = {3, 4}
  // AdjList[2] = {3}
  // AdjList[3] = {}   // we use directed edges from left to right set only
  // AdjList[4] = {}

  int V = 5, Vleft = 3;                               // we ignore vertex 0
  AdjList.assign(V, vi());
  AdjList[1].push_back(3); AdjList[1].push_back(4);
  AdjList[2].push_back(3);

  int MCBM = 0;
  match.assign(V, -1);    // V is the number of vertices in bipartite graph
  for (int L = 0; L < Vleft; L++) {         // Vleft = size of the left set
    vis.assign(Vleft, 0);                    // reset before each recursion
    MCBM += Aug(L);
  }
  printf("Found %d matchings\n", MCBM);  // the answer is 2 for Figure 4.42

  return 0;
}
