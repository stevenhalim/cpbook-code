import java.util.*;
import java.io.*;

public class ch4_07_floyd_warshall {
  public static void main(String[] args) throws Exception {
    int i, j, k, V, E, a, b, weight;

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

    V = sc.nextInt();
    E = sc.nextInt();
    
    int[][] AdjMat = new int[V][];
    for (i = 0; i < V; i++) {
      AdjMat[i] = new int[V];
      for (j = 0; j < V; j++)
        AdjMat[i][j] = 1000000000; // use 1.10^9 to avoid overflow
      AdjMat[i][i] = 0;
    }

    for (i = 0; i < E; i++) {
      a = sc.nextInt();
      b = sc.nextInt();
      weight = sc.nextInt();
      AdjMat[a][b] = weight; // directed graph
    }

    for (k = 0; k < V; k++) // O(v^3) Floyd Warshall's code is here
      for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
          AdjMat[i][j] = Math.min(AdjMat[i][j],
                         AdjMat[i][k] + AdjMat[k][j]);

    for (i = 0; i < V; i++)
      for (j = 0; j < V; j++)
        System.out.printf("APSP(%d, %d) = %d\n", i, j, AdjMat[i][j]);
  }
}
