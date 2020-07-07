// Distributing Ballot Boxes

import java.util.*;
import java.io.*;

class ballotboxes_UVa12390_TLE {
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    String[] tokens;
    while (true) {
      tokens = br.readLine().split(" ");
      int N = Integer.parseInt(tokens[0]), B = Integer.parseInt(tokens[1]);
      if ((N == -1) && (B == -1)) break;
      PriorityQueue<DII> pq = new PriorityQueue<>(); // min PQ
      for (int i = 0; i < N; ++i) {
        int a = Integer.parseInt(br.readLine());
        pq.add(new DII((double)-a/1.0, a, 1));   // initially, 1 box/city
      }
      br.readLine();                             // skip dummy line
      B -= N;                                    // remaining boxes
      while (B-- > 0) {                          // extra box->largest city
        DII f = pq.poll();                       // current largest city
        double r = -f.first();
        int num = f.second(), den = f.third();
        pq.add(new DII(-num/(den+1.0), num, den+1)); // reduce its workload
      }
      DII f = pq.peek();
      System.out.println((int)Math.ceil(-f.first())); // the final answer
    } // all other cities in the max pq will have equal or lesser ratio
  }
}

class DII implements Comparable<DII> {           // (ratio r, num, den)
  Double _first;
  Integer _second, _third;

  public DII(Double f, Integer s, Integer t) {
    _first = f;
    _second = s;
    _third = t;
  }

  public int compareTo(DII o) {
    if (Math.abs(this.first() - o.first()) > 1e-9)
      return this.first() - o.first() > 0 ? 1 : -1;
    else if (!this.second().equals(o.second()))
      return this.second() - o.second();
    else
      return this.third() - o.third();
  }

  Double first() { return _first; }
  Integer second() { return _second; }
  Integer third() { return _third; }

  public String toString() { return first() + " " + second() + " " + third(); }
}
