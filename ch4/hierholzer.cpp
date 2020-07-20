#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int N;
vector<vi> AL;                                   // Directed graph

vi hierholzer(int s) {
  vi ans, idx(N, 0), st;
  st.push_back(s);
  while (!st.empty()) {
    int u = st.back();
    if (idx[u] < (int)AL[u].size()) {            // still has neighbor
      st.push_back(AL[u][idx[u]]);
      ++idx[u];
    }
    else {
      ans.push_back(u);
      st.pop_back();
    }
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
  // The directed graph shown in Figure 4.40
  N = 7;
  AL.assign(N, {});
  AL[0] = {1, 6}; // A->[B,G]
  AL[1] = {2};    // B->C
  AL[2] = {3, 4}; // C->[D,E]
  AL[3] = {0};    // D->A
  AL[4] = {5};    // E->F
  AL[5] = {0, 2}; // F->[A,C]
  AL[6] = {5};    // G->F
  vi ans = hierholzer(0);
  for (auto &u : ans)
    cout << (char)('A'+u) << " ";
  cout << "\n";
  return 0;  
}
