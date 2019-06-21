// Come and Go
// check if the graph is strongly connected, i.e. the SCC of the graph is the graph itself (only 1 SCC)
// 0.835s in Java, 0.092s in C++

import java.util.*;
import java.io.*;

class IntegerPair implements Comparable {
  Integer _first, _second;

  public IntegerPair(Integer f, Integer s) {
    _first = f;
    _second = s;
  }

  public int compareTo(Object o) {
    if (this.first() != ((IntegerPair )o).first())
      return this.first() - ((IntegerPair )o).first();
    else
      return this.second() - ((IntegerPair )o).second();
  }

  Integer first() { return _first; }
  Integer second() { return _second; }
}

class Main {
  public static final int DFS_WHITE = -1;

  public static int i, j, N, M, V, W, P, numSCC;
  public static Vector < Vector < IntegerPair > > AdjList, AdjListT;
  public static Vector < Integer > dfs_num, S; // global variables

  public static void Kosaraju(int u, int pass) { // pass = 1 (original), 2 (transpose)
    dfs_num.set(u, 1);
    Vector < IntegerPair > neighbor;
    if (pass == 1) neighbor = AdjList.get(u); else neighbor = AdjListT.get(u);
    for (int j = 0; j < neighbor.size(); j++) {
      IntegerPair v = neighbor.get(j);
      if (dfs_num.get(v.first()) == DFS_WHITE)
        Kosaraju(v.first(), pass);
    }
    S.add(u); // as in finding topological order in Section 4.2.5
  }

  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    StringTokenizer st;

    while (true) {
      st = new StringTokenizer(br.readLine());
      N = Integer.parseInt(st.nextToken()); M = Integer.parseInt(st.nextToken());
      if (N == 0 && M == 0) break;

      AdjList = new Vector < Vector < IntegerPair > > ();
      AdjListT = new Vector < Vector < IntegerPair > > (); // the transposed graph
      for (i = 0; i < N; i++) {
        AdjList.add(new Vector < IntegerPair >());
        AdjListT.add(new Vector < IntegerPair >());
      }

      for (i = 0; i < M; i++) {
        st = new StringTokenizer(br.readLine());
        V = Integer.parseInt(st.nextToken()); W = Integer.parseInt(st.nextToken()); P = Integer.parseInt(st.nextToken());
        V--; W--;
        AdjList.get(V).add(new IntegerPair(W, 1)); // always
        AdjListT.get(W).add(new IntegerPair(V, 1));
        if (P == 2) { // if this is two way, add the reverse direction
          AdjList.get(W).add(new IntegerPair(V, 1));
          AdjListT.get(V).add(new IntegerPair(W, 1));
        }
      }

      // run Kosaraju's SCC code here
      S = new Vector < Integer > (); // first pass is to record the `post-order' of original graph
      dfs_num = new Vector < Integer > ();

      for (i = 0; i < N; i++)
        dfs_num.add(DFS_WHITE);
      for (i = 0; i < N; i++)
        if (dfs_num.get(i) == DFS_WHITE)
          Kosaraju(i, 1);

      numSCC = 0; // second pass: explore the SCCs based on first pass result
      dfs_num = new Vector < Integer > ();
      for (i = 0; i < N; i++)
        dfs_num.add(DFS_WHITE);
      for (i = N-1; i >= 0; i--)
        if (dfs_num.get(S.get(i)) == DFS_WHITE) {
          numSCC++;
          Kosaraju(S.get(i), 2);
        }

      // if SCC is only 1, print 1, otherwise, print 0
      pr.printf("%d\n", numSCC == 1 ? 1 : 0);
    }

    pr.close();
  }
}
