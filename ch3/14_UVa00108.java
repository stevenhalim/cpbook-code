import java.util.*;

class Main { /* Maximum Sum, 0.528s in UVa (C++ version runs in 0.008s) */
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int i, j, l, r, row, n, maxSubRect, subRect;
    int[][] A = new int[101][101];

    n = sc.nextInt();
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++) {
        A[i][j] = sc.nextInt();
        if (j > 0) A[i][j] += A[i][j - 1]; // pre-processing
      }

    maxSubRect = -127*100*100;    // the lowest possible value for this problem
    for (l = 0; l < n; l++) for (r = l; r < n; r++) {
      subRect = 0;
      for (row = 0; row < n; row++) {
        // Max 1D Range Sum on columns of this row i
        if (l > 0) subRect += A[row][r] - A[row][l - 1];
        else       subRect += A[row][r];

        // Kadane's algorithm on rows
        if (subRect < 0) subRect = 0;
        maxSubRect = Math.max(maxSubRect, subRect);
    } }

    System.out.printf("%d\n", maxSubRect);
} }
