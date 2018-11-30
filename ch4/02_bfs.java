import java.util.*;
import java.io.*;

public class ch4_04_bfs {
  private static int V, E, a, b, s;
  private static Vector< Vector< IntegerPair > > AdjList =
             new Vector< Vector< IntegerPair > >();
  private static Vector < Integer > p = new Vector < Integer > ();

  private static void printpath(int u) {
    if (u == s) { System.out.printf("%d", u); return; }
    printpath(p.get(u));
    System.out.printf(" %d", u);
  }
  
  public static void main(String[] args) throws Exception {
    /*
    // Graph in Figure 4.3, format: list of unweighted edges
    // This example shows another form of reading graph input
    13 16
    0 1    1 2    2  3   0  4   1  5   2  6    3  7   5  6
    4 8    8 9    5 10   6 11   7 12   9 10   10 11  11 12
    */

    File f = new File("in_04.txt");
    Scanner sc = new Scanner(f);

    V = sc.nextInt();
    E = sc.nextInt();

    AdjList.clear();
    for (int i = 0; i < V; i++) {
      Vector< IntegerPair > Neighbor = new Vector < IntegerPair >();
      AdjList.add(Neighbor); // add neighbor list to Adjacency List
    }

    for (int i = 0; i < E; i++) {
      a = sc.nextInt();
      b = sc.nextInt();
      AdjList.get(a).add(new IntegerPair(b, 0));
      AdjList.get(b).add(new IntegerPair(a, 0));
    }

    // as an example, we start from this source, see Figure 4.3
    s = 5;

    // BFS routine
    // inside void main(String[] args) -- we do not use recursion, thus we do not need to create separate function!
    Vector<Integer> dist = new Vector<Integer>();
    dist.addAll(Collections.nCopies(V, 1000000000));
    dist.set(s, 0); // start from source
    Queue<Integer> q = new LinkedList<Integer>(); q.offer(s);
    p.clear();
    p.addAll(Collections.nCopies(V, -1)); // to store parent information (p must be a global variable!)
    int layer = -1; // for our output printing purpose
    Boolean isBipartite = true;

    while (!q.isEmpty()) {
      int u = q.poll(); // queue: layer by layer!
      if (dist.get(u) != layer) System.out.printf("\nLayer %d:", dist.get(u));
      layer = dist.get(u);
      System.out.printf(", visit %d", u);
      Iterator it = AdjList.get(u).iterator();
      while (it.hasNext()) { // for each neighbours of u
        IntegerPair v = (IntegerPair)it.next();
        if (dist.get(v.first()) == 1000000000) { // if v not visited before
          dist.set(v.first(), dist.get(u) + 1); // then v is reachable from u
          q.offer(v.first()); // enqueue v for next steps
          p.set(v.first(), u); // parent of v is u
        }
        else if ((dist.get(v.first()) % 2) == (dist.get(u) % 2))              // same parity
          isBipartite = false;
      }
    }

    System.out.printf("\nShortest path: ");
    printpath(7); System.out.printf("\n");
    System.out.printf("isBipartite? %d\n", isBipartite ? 1 : 0);
  }
}