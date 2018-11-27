import java.io.*;
import java.util.*;

class pair < X, Y > { // utilizing Java "Generics"
  X _first;
  Y _second;

  public pair(X f, Y s) { _first = f; _second = s; }

  X first() { return _first; }
  Y second() { return _second; }

  void setFirst(X f) { _first = f; }
  void setSecond(Y s) { _second = s; }
}

class ch2_07_graph_ds {
  public static void main(String[] args) throws Exception {
    int V, E, total_neighbors, id, weight, a, b;

    // Try this input for Adjacency Matrix/List/EdgeList
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

    File f = new File("in_07.txt");
    Scanner sc = new Scanner(f);
    V = sc.nextInt(); // we must know this size first!
                      // remember that if V is > 100, try NOT to use AdjMat!
    int[][] AdjMat = new int[V][];
    for (int i = 0; i < V; i++) {
      AdjMat[i] = new int[V];
      for (int j = 0; j < V; j++)
        AdjMat[i][j] = sc.nextInt();
    }

    System.out.println("Neighbors of vertex 0:");
    for (int j = 0; j < V; j++) // O(|V|)
      if (AdjMat[0][j] != 0)
        System.out.println("Edge 0-" + j + " (weight = " + AdjMat[0][j] + ")");

    V = sc.nextInt();
    Vector< Vector< pair < Integer, Integer > > > AdjList = new Vector< Vector< pair < Integer, Integer > > >(V);
    for (int i = 0; i < V; i++) { // for each vertex
      Vector< pair < Integer, Integer > > Neighbor = new Vector < pair < Integer, Integer > >();
      AdjList.add(Neighbor); // add this empty neighbor list to Adjacency List
    }

    for (int i = 0; i < V; i++) {
      total_neighbors = sc.nextInt();
      for (int j = 0; j < total_neighbors; j++) {
        id = sc.nextInt();
        weight = sc.nextInt();
        AdjList.get(i).add( new pair < Integer, Integer > (id - 1, weight)); // some index adjustment
      }
    }

    System.out.println("Neighbors of vertex 0:");
    Iterator it = AdjList.get(0).iterator(); // AdjList[0] contains the required information
    while (it.hasNext()) { // O(k), where k is the number of neighbors
      pair< Integer, Integer > val = (pair< Integer, Integer >)it.next();
      System.out.println("Edge 0-" + val.first() + " (weight = " + val.second() + ")");
    }

    E = sc.nextInt();
    PriorityQueue < pair < Integer, pair < Integer, Integer > > > EdgeList = new PriorityQueue < pair < Integer, pair < Integer, Integer > > >(1, 
      new Comparator< pair < Integer, pair < Integer, Integer > > >() { // overriding the compare method
        public int compare(pair < Integer, pair < Integer, Integer > > i, pair < Integer, pair < Integer, Integer > > j) {
          return i.first() - j.first(); // currently min heap based on cost
        }
      }
    );

    for (int i = 0; i < E; i++) {
      a = sc.nextInt();
      b = sc.nextInt();
      pair < Integer, Integer > ab = new pair < Integer, Integer > (a, b);
      weight = sc.nextInt();
      EdgeList.offer(new pair < Integer, pair < Integer, Integer > > 
                               (-weight,  ab) ); // trick to reverse sort order */
    }

    // edges sorted by weight (smallest->largest)
    for (int i = 0; i < E; i++) {
      pair < Integer, pair < Integer, Integer > > edge = EdgeList.poll();
      // negate the weight again
      System.out.println("weight: " + (-edge.first()) + " (" + edge.second().first() + "-" + edge.second().second() + ")");
    }
  }
}
