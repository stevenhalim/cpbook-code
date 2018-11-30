// Sending email
// standard SSSP problem
// demo using SPFA only
// 2.442s in Java, 0.185s in C++

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
  public static int i, j, t, n, m, S, T, a, b, w, caseNo = 1;
  public static Vector < Vector < IntegerPair> > AdjList;
  public static final int INF = 2000000000;

  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    StringTokenizer st;

    t = Integer.parseInt(br.readLine());
    while (t-- > 0) {
      st = new StringTokenizer(br.readLine());
      n = Integer.parseInt(st.nextToken()); m = Integer.parseInt(st.nextToken());
      S = Integer.parseInt(st.nextToken()); T = Integer.parseInt(st.nextToken());

      // build graph
      AdjList = new Vector < Vector < IntegerPair > > ();
      for (i = 0; i < n; i++)
        AdjList.add(new Vector < IntegerPair > ());

      while (m-- > 0) {
        st = new StringTokenizer(br.readLine());
        a = Integer.parseInt(st.nextToken()); b = Integer.parseInt(st.nextToken()); w = Integer.parseInt(st.nextToken());
        AdjList.get(a).add(new IntegerPair(b, w)); // bidirectional
        AdjList.get(b).add(new IntegerPair(a, w));
      }

      // SPFA from source S
      // initially, only S has dist = 0 and in the queue
      Vector < Integer > dist = new Vector < Integer >();
      for (i = 0; i < n; i++)
        dist.add(INF);
      dist.set(S, 0);
      Queue < Integer > q = new LinkedList < Integer >();
      q.offer(S);
      Vector < Boolean > in_queue = new Vector < Boolean > ();
      for (i = 0; i < n; i++)
        in_queue.add(false);
      in_queue.set(S, true);


      while (!q.isEmpty()) {
        int u = q.peek(); q.poll(); in_queue.set(u, false);
        for (j = 0; j < AdjList.get(u).size(); j++) { // all outgoing edges from u
          int v = AdjList.get(u).get(j).first(), weight_u_v = AdjList.get(u).get(j).second();
          if (dist.get(u) + weight_u_v < dist.get(v)) { // if can relax
            dist.set(v, dist.get(u) + weight_u_v); // relax
            if (!in_queue.get(v)) { // add to the queue only if it's not in the queue
              q.offer(v);
              in_queue.set(v, true);
            }
          }
        }
      }

      pr.printf("Case #%d: ", caseNo++);
      if (dist.get(T) != INF) pr.printf("%d\n", dist.get(T));
      else                    pr.printf("unreachable\n");
    }

  pr.close();
  }
}
