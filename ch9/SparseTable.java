import java.util.*;

class RMQ {                                          // Range Minimum Query
  private int[] _A = new int[1000];          // adjust this value as needed
  private int[][] SpT = new int[1000][10];

  public RMQ(int n, int[] A) { // constructor as well as pre-processing routine
    for (int i = 0; i < n; i++) {
      _A[i] = A[i];
      SpT[i][0] = i; // RMQ of sub array starting at index i + length 2^0=1
    }
    // the two nested loops below have overall time complexity = O(n log n)
    for (int j = 1; (1<<j) <= n; j++) // for each j s.t. 2^j <= n, O(log n)
      for (int i = 0; i + (1<<j) - 1 < n; i++)    // for each valid i, O(n)
        if (_A[SpT[i][j-1]] < _A[SpT[i+(1<<(j-1))][j-1]])            // RMQ
          SpT[i][j] = SpT[i][j-1];    // start at index i of length 2^(j-1)
        else                  // start at index i+2^(j-1) of length 2^(j-1)
          SpT[i][j] = SpT[i+(1<<(j-1))][j-1];
  }

  public int query(int i, int j) {
    int k = (int)Math.floor(Math.log((double)j-i+1) / Math.log(2.0)); // 2^k <= (j-i+1)
    if (_A[SpT[i][k]] <= _A[SpT[j-(1<<k)+1][k]]) return SpT[i][k];
    else                                         return SpT[j-(1<<k)+1][k];
} };

class SparseTable {
  public static void main(String[] args) {
    // same example as in chapter 2: segment tree
    int n = 7;
    int[] A = new int[] {18, 17, 13, 19, 15, 11, 20};
    RMQ rmq = new RMQ(n, A);
    for (int i = 0; i < n; i++)
      for (int j = i; j < n; j++)
        System.out.printf("RMQ(%d, %d) = %d\n", i, j, rmq.query(i, j));
  }
}
