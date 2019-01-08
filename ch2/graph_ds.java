import java.io.*;
import java.util.*;

class pair<X, Y> { // utilizing Java "Generics"
  X _first;
  Y _second;

  public pair(X f, Y s) { _first = f; _second = s; }

  X first() { return _first; }
  Y second() { return _second; }

  void setFirst(X f) { _first = f; }
  void setSecond(Y s) { _second = s; }
}

class graph_ds {
  public static void main(String[] args) throws Exception {
    // Try this input for Adjacency Matrix/List/EL
    // Adj Matrix
    //   for each line: |V| entries, 0 or the weight
    // Adj List
    //   for each line: num neighbors, list of neighbors + weight pairs
    // Edge List
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
    for (int i = 0; i < V; i++) {
      AM[i] = new int[V];
      for (int j = 0; j < V; j++)
        AM[i][j] = sc.nextInt();
    }

    System.out.println("Neighbors of vertex 0:");
    for (int j = 0; j < V; j++) // O(|V|)
      if (AM[0][j] != 0)
        System.out.println("Edge 0-" + j + " (weight = " + AM[0][j] + ")");

    V = sc.nextInt();
    Vector< Vector< pair < Integer, Integer > > > AL = new Vector< Vector< pair < Integer, Integer > > >(V);
    for (int i = 0; i < V; i++) { // for each vertex
      Vector< pair < Integer, Integer > > Neighbor = new Vector < pair < Integer, Integer > >();
      AL.add(Neighbor); // add this empty neighbor list to Adjacency List
    }

    for (int i = 0; i < V; i++) {
      int total_neighbors = sc.nextInt();
      for (int j = 0; j < total_neighbors; j++) {
        int id = sc.nextInt();
        int weight = sc.nextInt();
        AL.get(i).add(new pair<Integer, Integer>(id-1, weight)); // some index adjustment
      }
    }

    System.out.println("Neighbors of vertex 0:");
    for (pair<Integer, Integer> v_w : AL.get(0)) {
      int v = v_w.first(), w = v_w.second();
      System.out.println("Edge 0-" + v + " (weight = " + w + ")");
    }

    int E = sc.nextInt();
    PriorityQueue<pair<Integer, pair<Integer, Integer>>> EL = new PriorityQueue<>(1, 
      new Comparator<pair<Integer, pair<Integer, Integer>>>() { // overriding the compare method
        public int compare(pair<Integer, pair<Integer, Integer>> i, pair<Integer, pair<Integer, Integer>> j) {
          return i.first() - j.first(); // currently min heap based on cost
        }
      }
    );

    for (int i = 0; i < E; i++) {
      int a = sc.nextInt();
      int b = sc.nextInt();
      pair<Integer, Integer> ab = new pair<>(a, b);
      int weight = sc.nextInt();
      EL.offer(new pair<Integer, pair<Integer, Integer>> (-weight, ab) ); // to reverse sort order
    }

    // edges sorted by weight (smallest->largest)
    for (int i = 0; i < E; i++) {
      pair < Integer, pair < Integer, Integer > > edge = EL.poll();
      // negate the weight again
      System.out.println("weight: " + (-edge.first()) + " (" + edge.second().first() + "-" + edge.second().second() + ")");
    }
  }
}
