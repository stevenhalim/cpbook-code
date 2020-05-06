import java.util.*;

class string_alignment {
  public static void main(String[] args){
    char[] A = "ACAATCC".toCharArray(), B = "AGCATGC".toCharArray();
    int[][] table = new int[20][20]; // Needleman Wunsnch's algorithm
    int n = A.length, m = B.length;

    // insert/delete = -1 point
    for (int i = 1; i <= n; ++i)
      table[i][0] = i * -1;
    for (int j = 1; j <= m; ++j)
      table[0][j] = j * -1;

    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j) {
        // match = 2 points, mismatch = -1 point
        table[i][j] = table[i - 1][j - 1] + (A[i - 1] == B[j - 1] ? 2 : -1); // cost for match or mismatches
        // insert/delete = -1 point
        table[i][j] = Math.max(table[i][j], table[i - 1][j] - 1); // delete
        table[i][j] = Math.max(table[i][j], table[i][j - 1] - 1); // insert
      }

    System.out.printf("DP table:\n");
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= m; ++j)
        System.out.printf("%3d", table[i][j]);
      System.out.printf("\n");
    }
    System.out.printf("Maximum Alignment Score: %d\n", table[n][m]);
  }
}
