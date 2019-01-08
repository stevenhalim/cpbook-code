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

    File f = new File("in_07.txt");    
    Scanner sc = new Scanner(f);

    int V = sc.nextInt();
    int E = sc.nextInt();
    
    int[][] AM = new int[V][];
    for (int i = 0; i < V; i++) {
      AM[i] = new int[V];
      for (int j = 0; j < V; j++)
        AM[i][j] = 1000000000; // use 1.10^9 to avoid overflow
      AM[i][i] = 0;
    }

    for (int i = 0; i < E; i++) {
      int u = sc.nextInt();
      int v = sc.nextInt();
      int w = sc.nextInt();
      AM[u][v] = w;                                       // directed graph
    }

    for (int k = 0; k < V; k++)     // O(v^3) Floyd Warshall's code is here
      for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
          AM[i][j] = Math.min(AM[i][j], AM[i][k]+AM[k][j]);

    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++)
        System.out.printf("APSP(%d, %d) = %d\n", i, j, AM[i][j]);
  }
}
