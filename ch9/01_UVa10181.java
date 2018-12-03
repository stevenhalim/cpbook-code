// 15-Puzzle Problem with IDA*, 2.975s in Java, 1.758s in C++

import java.util.*;
import java.io.*;

class ch8_01_UVa10181 {
  static final int INF = 1000000000;
  static final int ROW_SIZE = 4; // ROW_SIZE is a matrix of 4 x 4
  static final int PUZZLE = (ROW_SIZE*ROW_SIZE);
  static final int X = 15;

  static int[] p = new int[PUZZLE];
  static int lim, nlim;
  static int[] dr = new int[] { 0,-1, 0, 1}; // E,N,W,S
  static int[] dc = new int[] { 1, 0,-1, 0}; // R,U,L,D
  static TreeMap<Integer, Integer> pred = new TreeMap<Integer, Integer>();
  static TreeMap<Long, Integer> vis = new TreeMap<Long, Integer>();
  static char[] ans = new char[] {'R', 'U', 'L', 'D'};

  static int h1() { // heuristic: sum of Manhattan distances (compute all)
    int ans = 0;
    for (int i = 0; i < PUZZLE; i++) {
      int tgt_i = p[i] / 4, tgt_j = p[i] % 4;
      if (p[i] != X)
        ans += Math.abs(i / 4 - tgt_i) + Math.abs(i % 4 - tgt_j); // Manhattan distance
    }
    return ans;
  }

  static int h2(int i1, int j1, int i2, int j2) { // heuristic: sum of manhattan distances (compute delta)
    int tgt_i = p[i2 * 4 + j2] / 4, tgt_j = p[i2 * 4 + j2] % 4;
    return -(Math.abs(i2 - tgt_i) + Math.abs(j2 - tgt_j)) + (Math.abs(i1 - tgt_i) + Math.abs(j1 - tgt_j));
  }

  static boolean goal() {
    for (int i = 0; i < PUZZLE; i++)
      if (p[i] != X && p[i] != i)
        return false;
    return true;
  }

  static boolean valid(int r, int c) {
    return 0 <= r && r < 4 && 0 <= c && c < 4;
  }

  static void swap(int i, int j, int new_i, int new_j) {
    int temp = p[i * 4 + j];
    p[i * 4 + j] = p[new_i * 4 + new_j];
    p[new_i * 4 + new_j] = temp;
  }

  static boolean DFS(int g, int h) {
    if (g + h > lim) {
      nlim = Math.min(nlim, g + h);
      return false;
    }

    if (goal())
      return true;

    long state = 0;
    for (int i = 0; i < PUZZLE; i++) { // transform 16 numbers into 64 bits, exactly into ULL
      state <<= 4; // move left 4 bits
      state += p[i]; // add this digit (max 15 or 1111)
    }

    if (vis.containsKey(state) && vis.get(state) <= g) // not pure backtracking... this is to prevent cycling
      return false; // not good
    vis.put(state, g); // mark this as visited

    int i, j, d, new_i, new_j;
    for (i = 0; i < PUZZLE; i++)
      if (p[i] == X)
        break;
    j = i % 4;
    i /= 4;

    for (d = 0; d < 4; d++) {
      new_i = i + dr[d]; new_j = j + dc[d];
      if (valid(new_i, new_j)) {
        int dh = h2(i, j, new_i, new_j);
        swap(i, j, new_i, new_j); // swap first
        pred.put(g + 1, d);
        if (DFS(g + 1, h + dh)) // if ok, no need to restore, just go ahead
          return true;
        swap(i, j, new_i, new_j); // restore
      }
    }

    return false;
  }

  static int IDA_Star() {
    lim = h1();
    while (true) {
      nlim = INF; // next limit
      pred.clear();
      vis.clear();
      if (DFS(0, h1()))
        return lim; 
      if (nlim == INF)
        return -1;
      lim = nlim; // nlim > lim
      if (lim > 45) // pruning condition in the problem
        return -1;
    }
  }

  static void output(int d) {
    if (d == 0)
      return;
    output(d - 1);
    System.out.printf("%c", ans[pred.get(d)]);
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    int N = sc.nextInt();
    while (N-- > 0) {
      int i, j, blank = 0, sum = 0, ans = 0;
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) {
          p[i * 4 + j] = sc.nextInt();
          if (p[i * 4 + j] == 0) {
            p[i * 4 + j] = X; // change to X (15)
            blank = i * 4 + j; // remember the index
          }
          else
            p[i * 4 + j]--; // use 0-based indexing
        }

      for (i = 0; i < PUZZLE; i++)
        for (j = 0; j < i; j++)
          if (p[i] != X && p[j] != X && p[j] > p[i])
            sum++;
      sum += blank / ROW_SIZE;

      if (sum % 2 != 0 && ((ans = IDA_Star()) != -1)) {
        output(ans);
        System.out.printf("\n");
      }
      else
        System.out.printf("This puzzle is not solvable.\n");
    }
  }
}
