// Come and Go
// check if the graph is strongly connected, i.e. the SCC of the graph is the graph itself (only 1 SCC)
// 0.835s in Java, 0.092s in C++

import java.util.*;
import java.io.*;

class IntegerPair implements Comparable<IntegerPair> {
  Integer _first, _second;

  public IntegerPair(Integer f, Integer s) {
    _first = f;
    _second = s;
  }

  public int compareTo(IntegerPair o) {
    if (!this.first().equals(o.first()))
      return this.first() - o.first();
    else
      return this.second() - o.second();
  }

  Integer first() { return _first; }
  Integer second() { return _second; }
}

class Main {
  private static final int UNVISITED = 0;

  private static int dfsNumberCounter, numSCC;
  private static ArrayList<ArrayList<IntegerPair>> AL, AL_T;
  private static ArrayList<Integer> dfs_num, dfs_low, S, visited; // global variables
  private static Stack<Integer> St;

  private static void tarjanSCC(int u) {
    dfs_num.set(u, dfsNumberCounter);
    dfs_low.set(u, dfsNumberCounter++);          // dfs_low[u] <= dfs_num[u]
    St.push(u); // stores u in a vector based on order of visitation
    visited.set(u, 1);

    for (IntegerPair v_w : AL.get(u)) {
      if (dfs_num.get(v_w.first()) == UNVISITED) // a tree edge
        tarjanSCC(v_w.first());
      if (visited.get(v_w.first()) == 1) // condition for update
        dfs_low.set(u, Math.min(dfs_low.get(u), dfs_low.get(v_w.first())));
    }

    if (dfs_low.get(u) == dfs_num.get(u)) {      // a root/start of an SCC
      ++numSCC;
      while (true) {
        int v = St.peek(); St.pop(); visited.set(v, 0);
        if (u == v) break;
      }
    }
  }

  public static void Kosaraju(int u, int pass) { // pass = 1 (original), 2 (transpose)
    dfs_num.set(u, 1);
    ArrayList<IntegerPair> neighbor = (pass == 1) ? AL.get(u) : AL_T.get(u);
    for (int j = 0; j < neighbor.size(); j++) {
      IntegerPair v = neighbor.get(j);
      if (dfs_num.get(v.first()) == UNVISITED)
        Kosaraju(v.first(), pass);
    }
    S.add(u); // as in finding topological order in Section 4.2.5
  }

  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    while (true) {
      String[] token = br.readLine().split(" ");
      int N = Integer.parseInt(token[0]), M = Integer.parseInt(token[1]);
      if (N == 0 && M == 0) break;

      AL = new ArrayList<>();
      AL_T = new ArrayList<>(); // the transposed graph
      for (int u = 0; u < N; ++u) {
        AL.add(new ArrayList<>());
        AL_T.add(new ArrayList<>());
      }

      while (M-- > 0) {
        token = br.readLine().split(" ");
        int V = Integer.parseInt(token[0])-1, W = Integer.parseInt(token[1])-1, P = Integer.parseInt(token[2]);
        AL.get(V).add(new IntegerPair(W, 1)); // always
        AL_T.get(W).add(new IntegerPair(V, 1));
        if (P == 2) { // if this is two way, add the reverse direction
          AL.get(W).add(new IntegerPair(V, 1));
          AL_T.get(V).add(new IntegerPair(W, 1));
        }
      }

      // run Tarjan's SCC code here
      // dfs_num = new ArrayList<>(Collections.nCopies(N, UNVISITED));
      // dfs_low = new ArrayList<>(Collections.nCopies(N, 0));
      // visited = new ArrayList<>(Collections.nCopies(N, 0));
      // St = new Stack<>();
      // dfsNumberCounter = numSCC = 0;
      // for (int u = 0; u < N; ++u)
      //   if (dfs_num.get(u) == UNVISITED)
      //     tarjanSCC(u);

      // run Kosaraju's SCC code here
      S = new ArrayList<>(); // first pass: record the post-order of original graph
      dfs_num = new ArrayList<>(Collections.nCopies(N, UNVISITED));
      for (int u = 0; u < N; ++u)
        if (dfs_num.get(u) == UNVISITED)
          Kosaraju(u, 1);
      int numSCC = 0; // second pass: explore SCCs using first pass order
      dfs_num = new ArrayList<>(Collections.nCopies(N, UNVISITED));
      for (int i = N-1; i >= 0; i--)
        if (dfs_num.get(S.get(i)) == UNVISITED) {
          ++numSCC;
          Kosaraju(S.get(i), 2);
        }

      // if SCC is only 1, print 1, otherwise, print 0
      pr.printf("%d\n", numSCC == 1 ? 1 : 0);
    }

    pr.close();
  }
}
