// Maximum Sum, 0.150s in UVa (C++ version runs in 0.000s)

import java.util.*;

class Main {                                     // UVa default class name
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int[][] A = new int[110][110];
    int n = sc.nextInt();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        A[i][j] = sc.nextInt();
        if (j > 0) A[i][j] += A[i][j-1];         // pre-processing
      }
    int maxSubRect = -127*100*100;               // the lowest possible val
    for (int l = 0; l < n; ++l)
      for (int r = l; r < n; ++r) {
        int subRect = 0;
        for (int row = 0; row < n; ++row) {
          // Max 1D Range Sum on columns of this row
          if (l > 0) subRect += A[row][r] - A[row][l-1];
          else       subRect += A[row][r];
          // Kadane's algorithm on rows
          if (subRect < 0) subRect = 0;          // restart if negative
          maxSubRect = Math.max(maxSubRect, subRect);
        }
      }
    System.out.printf("%d\n", maxSubRect);
  }
}
