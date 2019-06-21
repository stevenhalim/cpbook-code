import java.io.*;
import java.util.*;

class graph_ds {
  public static void main(String[] args) throws Exception {
    // Try this input for Adjacency Matrix/Adjacency List/Edge List
    // Adjacency Matrix AM
    //   for each line: |V| entries, 0 or the weight
    // Adjacency List AL
    //   for each line: num neighbors, list of neighbors + weight pairs
    // Edge List EL
    //   for each line: a-b of edge(a,b) and weight
    /*
    6
      0  10   0   0 100   0
     10   0   7   0   8   0
      0   7   0   9   0   0
      0   0   9   0  20   5
    100   8   0  20   0   0
      0   0   0   5   0   0
    6
    2 2 10 5 100
    3 1 10 3 7 5 8
    2 2 7 4 9
    3 3 9 5 20 6 5
    3 1 100 2 8 4 20
    1 4 5
    7
    1 2 10
    1 5 100
    2 3 7
    2 5 8
    3 4 9
    4 5 20
    4 6 5
    */

    File f = new File("graph_ds.txt");
    Scanner sc = new Scanner(f);
    int V = sc.nextInt(); // we must know this size first!
                          // remember that if V is > 100, try NOT to use AM!
    int[][] AM = new int[V][];
    for (int u = 0; u < V; ++u) {
      AM[u] = new int[V];
      for (int v = 0; v < V; ++v)
        AM[u][v] = sc.nextInt();
    }

    System.out.println("Neighbors of vertex 0:");
    for (int v = 0; v < V; ++v) // O(|V|)
      if (AM[0][v] != 0)
        System.out.println("Edge 0-" + v + " (weight = " + AM[0][v] + ")");

    V = sc.nextInt();
    ArrayList<ArrayList<IntegerPair>> AL = new ArrayList<>(V);
    for (int u = 0; u < V; ++u) { // for each vertex
      ArrayList<IntegerPair> Neighbor = new ArrayList<>();
      AL.add(Neighbor); // add this empty neighbor list to Adjacency List
      int total_neighbors = sc.nextInt();
      while (total_neighbors-- > 0) {
        int v = sc.nextInt()-1, w = sc.nextInt(); // to 0-based indexing
        AL.get(u).add(new IntegerPair(v, w));
      }
    }

    System.out.println("Neighbors of vertex 0:");
    for (IntegerPair v_w : AL.get(0)) {
      int v = v_w.first(), w = v_w.second();
      System.out.println("Edge 0-" + v + " (weight = " + w + ")");
    }

    int E = sc.nextInt();
    ArrayList<IntegerTriple> EL = new ArrayList<>();
    for (int i = 0; i < E; ++i) {
      int u = sc.nextInt(), v = sc.nextInt(), w = sc.nextInt();
      EL.add(new IntegerTriple(w, u, v));
    }
    // edges sorted by weight (smallest->largest)
    Collections.sort(EL);
    for (int i = 0; i < E; i++) {
      IntegerTriple edge = EL.get(i);
      System.out.println("weight: " + edge.first() + " (" + edge.second() + "-" + edge.third() + ")");
    }
  }
}
