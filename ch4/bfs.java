import java.util.*;
import java.io.*;

public class bfs {
  private static int s;
  private static ArrayList<Integer> p = new ArrayList<>();

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

    File f = new File("bfs_in.txt");
    Scanner sc = new Scanner(f);

    int V = sc.nextInt();
    int E = sc.nextInt();

    ArrayList<ArrayList<IntegerPair>> AL = new ArrayList<>();
    for (int i = 0; i < V; i++) {
      ArrayList<IntegerPair> Neighbor = new ArrayList<>();
      AL.add(Neighbor); // add neighbor list to Adjacency List
    }

    for (int i = 0; i < E; i++) {
      int a = sc.nextInt();
      int b = sc.nextInt();
      AL.get(a).add(new IntegerPair(b, 0));
      AL.get(b).add(new IntegerPair(a, 0));
    }

    // as an example, we start from this source, see Figure 4.3
    s = 5;

    // BFS routine
    // inside void main(String[] args) -- we do not use recursion, thus we do not need to create separate function!
    ArrayList<Integer> dist = new ArrayList<>();
    dist.addAll(Collections.nCopies(V, 1000000000));
    dist.set(s, 0); // start from source
    Queue<Integer> q = new LinkedList<>(); q.offer(s);
    p.clear();
    p.addAll(Collections.nCopies(V, -1)); // to store parent information (p must be a global variable!)
    int layer = -1; // for our output printing purpose
    Boolean isBipartite = true;

    while (!q.isEmpty()) {
      int u = q.poll(); // queue: layer by layer!
      if (dist.get(u) != layer) System.out.printf("\nLayer %d:", dist.get(u));
      layer = dist.get(u);
      System.out.printf(", visit %d", u);
      Iterator it = AL.get(u).iterator();
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
