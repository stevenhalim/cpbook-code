import java.util.*;
import java.io.*;

public class floyd_warshall {
  public static void main(String[] args) throws Exception {
    /*
    // Graph in Figure 4.20
    5 9
    0 1 2
    0 2 1
    0 4 3
    1 3 4
    2 1 1
    2 4 1
    3 0 1
    3 2 3
    3 4 5
    */

    Scanner sc = new Scanner(new File("floyd_warshall_in.txt"));
    int V = sc.nextInt(), E = sc.nextInt();
    
    int[][] AM = new int[V][];
    for (int u = 0; u < V; ++u) {
      AM[u] = new int[V];
      for (int v = 0; v < V; ++v)
        AM[u][v] = 1000000000;                   // 1e9 to avoid overflow
      AM[u][u] = 0;
    }

    for (int i = 0; i < E; ++i) {
      int u = sc.nextInt(), v = sc.nextInt(), w = sc.nextInt();
      AM[u][v] = w;                              // directed graph
    }

    for (int k = 0; k < V; ++k)                  // O(v^3) Floyd Warshall's
      for (int u = 0; u < V; ++u)
        for (int v = 0; v < V; ++v)
          AM[u][v] = Math.min(AM[u][v], AM[u][k]+AM[k][v]);

    for (int u = 0; u < V; ++u)
      for (int v = 0; v < V; ++v)
        System.out.printf("APSP(%d, %d) = %d\n", u, v, AM[u][v]);
  }
}
