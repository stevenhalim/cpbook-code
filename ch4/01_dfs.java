import java.util.Collections;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Stack;
import java.util.Vector;
import java.io.*;

public class ch4_01_dfs {
  private static final int DFS_WHITE = -1; // normal DFS
  private static final int DFS_BLACK = 1;
  private static final int DFS_GRAY = 2;
  private static Vector < Vector < IntegerPair > > AdjList = 
             new Vector < Vector < IntegerPair > >();
  private static Vector < Integer > dfs_num, dfs_low, dfs_parent;
  private static Vector < Boolean > articulation_vertex, visited;
  private static Stack < Integer > S; // additional information for SCC
  private static Vector < Integer > topologicalSort; // additional information for toposort
  private static int numComp, dfsNumberCounter, dfsRoot, rootChildren;

  private static void initDFS(int V) { // used in normal DFS
    dfs_num = new Vector < Integer > ();
    dfs_num.addAll(Collections.nCopies(V, DFS_WHITE));
    numComp = 0;
  }

  private static void initGraphCheck(int V) {
    initDFS(V);
    dfs_parent = new Vector < Integer > ();
    dfs_parent.addAll(Collections.nCopies(V, 0));
    numComp = 0;
  }

  private static void initArticulationPointBridge(int V) {
    initGraphCheck(V);
    dfs_low = new Vector < Integer > ();
    dfs_low.addAll(Collections.nCopies(V, 0));
    articulation_vertex = new Vector < Boolean > ();
    articulation_vertex.addAll(Collections.nCopies(V, false));
    dfsNumberCounter = 0;
  }

  private static void initTarjanSCC(int V) {
    initGraphCheck(V);
    dfs_low = new Vector < Integer > ();
    dfs_low.addAll(Collections.nCopies(V, 0));
    dfsNumberCounter = 0;
    numComp = 0;
    S = new Stack < Integer > ();
    visited = new Vector < Boolean > ();
    visited.addAll(Collections.nCopies(V, false));
  }

  private static void initTopologicalSort(int V) {
    initDFS(V);
    topologicalSort = new Vector < Integer > ();
  }

  private static void dfs(int u) { // DFS for normal usage
    System.out.printf(" %d", u); // this vertex is visited
    dfs_num.set(u, DFS_BLACK); // mark as visited
    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) { // try all neighbors v of vertex u
      IntegerPair v = (IntegerPair)it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE) // avoid cycle
        dfs(v.first()); // v is a (neighbor, weight) pair
    }
  }

  private static void floodfill(int u, int color) {
    dfs_num.set(u, color); // not just a generic DFS_BLACK
    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) { // try all neighbors v of vertex u
      IntegerPair v = (IntegerPair)it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE) // avoid cycle
        floodfill(v.first(), color); // v is a (edge, weight) pair
    }
  }

  private static void graphCheck(int u) { // DFS for checking graph edge properties...
    dfs_num.set(u, DFS_GRAY); // color this as DFS_GRAY (temporary)
    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) { // traverse this AdjList
      IntegerPair v = (IntegerPair)it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE) { // DFS_GRAY to DFS_WHITE
        // System.out.printf("  Tree Edge (%d, %d)\n", u, v.first());
        dfs_parent.set(v.first(), u); // parent of this children is me
        graphCheck(v.first());
      }
      else if (dfs_num.get(v.first()) == DFS_GRAY) { // DFS_GRAY to DFS_GRAY
        if (v.first() == dfs_parent.get(u))
          System.out.printf(" Bidirectional Edge (%d, %d) - (%d, %d)\n", u, v.first(), v.first(), u);
        else
          System.out.printf(" Back Edge (%d, %d) (Cycle)\n", u, v.first());
      }
      else if (dfs_num.get(v.first()) == DFS_BLACK) // DFS_GRAY to DFS_BLACK
        System.out.printf(" Forward/Cross Edge (%d, %d)\n", u, v.first());
    }
    dfs_num.set(u, DFS_BLACK); // now color this as DFS_BLACK (DONE)
  }

  private static void articulationPointAndBridge(int u) {
    dfs_low.set(u, dfsNumberCounter);
    dfs_num.set(u, dfsNumberCounter++); // dfs_low[u] <= dfs_num[u]
    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) { // try all neighbors v of vertex u
      IntegerPair v = (IntegerPair)it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE) { // a tree edge
        dfs_parent.set(v.first(), u); // parent of this children is me
        if (u == dfsRoot) // special case
          rootChildren++; // count children of root
        articulationPointAndBridge(v.first());
        if (dfs_low.get(v.first()) >= dfs_num.get(u)) // for articulation point
          articulation_vertex.set(u, true); // store this information first
        if (dfs_low.get(v.first()) > dfs_num.get(u)) // for bridge
          System.out.printf(" Edge (%d, %d) is a bridge\n", u, v.first());
        dfs_low.set(u, Math.min(dfs_low.get(u), dfs_low.get(v.first()))); // update dfs_low[u]
      }
      else if (v.first() != dfs_parent.get(u)) // a back edge and not direct cycle
        dfs_low.set(u, Math.min(dfs_low.get(u), dfs_num.get(v.first()))); // update dfs_low[u]
    }
  }

  private static void tarjanSCC(int u) {
    dfs_num.set(u, dfsNumberCounter);
    dfs_low.set(u, dfsNumberCounter++); // dfs_low[u] <= dfs_num[u]
    S.push(u); // store u according to order of visitation
    visited.set(u, true);

    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) { // try all neighbors v of vertex u
      IntegerPair v = (IntegerPair)it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE) // a tree edge
        tarjanSCC(v.first());
      if (visited.get(v.first())) // condition for update
        dfs_low.set(u, Math.min(dfs_low.get(u), dfs_low.get(v.first())));
    }

    if (dfs_low.get(u) == dfs_num.get(u)) { // if this is a root (start) of an SCC
      System.out.printf("SCC %d: ", ++numComp);
      while (true) {
        int v = S.peek(); S.pop(); visited.set(v, false);
        System.out.printf(" %d", v);
        if (u == v) break;
      }
      System.out.printf("\n");
    }
  }

  private static void topoVisit(int u) {
    dfs_num.set(u, DFS_BLACK);
    Iterator it = AdjList.get(u).iterator();
    while (it.hasNext()) {
      IntegerPair v = (IntegerPair)it.next();
      if (dfs_num.get(v.first()) == DFS_WHITE)
        topoVisit(v.first());
    }
    topologicalSort.add(u);
  }

  private static void printThis(String message) {
    System.out.printf("==================================\n");
    System.out.printf("%s\n", message);
    System.out.printf("==================================\n");
  }

  public static void main(String[] args) throws Exception {
    int i, j, V, total_neighbors, id, weight;

    /*
    // Use the following input:
    // Graph in Figure 4.1
    9
    1 1 0
    3 0 0 2 0 3 0
    2 1 0 3 0
    3 1 0 2 0 4 0
    1 3 0
    0
    2 7 0 8 0
    1 6 0
    1 6 0

    // Example of directed acyclic graph in Figure 4.4 (for toposort)
    8
    2 1 0 2 0
    2 2 0 3 0
    2 3 0 5 0
    1 4 0
    0
    0
    0
    1 6 0

    // Example of directed graph with back edges
    3
    1 1 0
    1 2 0
    1 0 0

    // Left graph in Figure 4.6/4.7/4.8
    6
    1 1 0
    3 0 0 2 0 4 0
    1 1 0
    1 4 0
    3 1 0 3 0 5 0
    1 4 0

    // Right graph in Figure 4.6/4.7/4.8
    6
    1 1 0
    5 0 0 2 0 3 0 4 0 5 0
    1 1 0
    1 1 0
    2 1 0 5 0
    2 1 0 4 0

    // Directed graph in Figure 4.9
    8
    1 1 0
    1 3 0
    1 1 0
    2 2 0 4 0
    1 5 0
    1 7 0
    1 4 0
    1 6 0
    */

    File f = new File("in_01.txt");
    Scanner sc = new Scanner(f);

    V = sc.nextInt();
    AdjList.clear();
    for (i = 0; i < V; i++) {
      Vector < IntegerPair > Neighbor = new Vector < IntegerPair >(); // create vector of pair<int, int> 
      AdjList.add(Neighbor); // store blank vector first
    }

    for (i = 0; i < V; i++) {
      total_neighbors = sc.nextInt();
      for (j = 0; j < total_neighbors; j++) {
        id = sc.nextInt();
        weight = sc.nextInt();
        AdjList.get(i).add(new IntegerPair(id, weight));
      }
    }

    initDFS(V); // call this first before running DFS
    printThis("Standard DFS Demo (the input graph must be UNDIRECTED)");
    for (i = 0; i < V; i++) // for each vertex i in [0..V-1]
      if (dfs_num.get(i) == DFS_WHITE) { // if not visited yet
        System.out.printf("Component %d, visit:", ++numComp);
        dfs(i);
        System.out.printf("\n");
      }
    System.out.printf("There are %d connected components\n", numComp);

    initDFS(V); // call this first before running DFS
    printThis("Flood Fill Demo (the input graph must be UNDIRECTED)");
    for (i = 0; i < V; i++) // for each vertex i in [0..V-1], note that we use our REP macro again
      if (dfs_num.get(i) == DFS_WHITE) // if not visited yet
        floodfill(i, ++numComp);
    for (i = 0; i < V; i++)
      System.out.printf("Vertex %d has color %d\n", i, dfs_num.get(i));

    // make sure that the given graph is DAG
    initTopologicalSort(V);
    printThis("Topological Sort (the input graph must be DAG)");
    for (i = 0; i < V; i++)
      if (dfs_num.get(i) == DFS_WHITE)
        topoVisit(i);
    for (i = topologicalSort.size() - 1; i >= 0; i--) // access from back to front
      System.out.printf(" %d", topologicalSort.get(i));
    System.out.printf("\n");

    initGraphCheck(V);
    printThis("Graph Edges Property Check");
    for (i = 0; i < V; i++)
      if (dfs_num.get(i) == DFS_WHITE) {
        System.out.printf("Component %d:\n", ++numComp);
        graphCheck(i);
      }

    initArticulationPointBridge(V);
    printThis("Articulation Points & Bridges (the input graph must be UNDIRECTED)");
    System.out.printf("Bridges:\n");
    for (i = 0; i < V; i++)
      if (dfs_num.get(i) == DFS_WHITE) {
        dfsRoot = i; rootChildren = 0;
        articulationPointAndBridge(i);
        articulation_vertex.set(dfsRoot, (rootChildren > 1)); // special case
      }

    System.out.printf("Articulation Points:\n");
    for (i = 0; i < V; i++)
      if (articulation_vertex.get(i))
        System.out.printf(" Vertex %d\n", i);

    initTarjanSCC(V);
    printThis("Strongly Connected Components (the input graph must be DIRECTED)");
    for (i = 0; i < V; i++)
      if (dfs_num.get(i) == DFS_WHITE)
        tarjanSCC(i);
  }
}
