// The Dragon of Loowater

import java.util.*;
import java.io.*;

class loowater_UVa11292 {
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    while (true) {
      String[] token = br.readLine().split(" ");
      int n = Integer.parseInt(token[0]), m = Integer.parseInt(token[1]);
      if ((n == 0) && (m == 0)) break;
      ArrayList<Integer> D = new ArrayList<>(n);
      ArrayList<Integer> H = new ArrayList<>(m);
      for (int d = 0; d < n; ++d) D.add(Integer.parseInt(br.readLine()));
      for (int k = 0; k < m; ++k) H.add(Integer.parseInt(br.readLine()));
      Collections.sort(D);                             // sorting is an important
      Collections.sort(H);                             // pre-processing step
      int gold = 0, d = 0, k = 0;                      // both arrays are sorted
      while ((d < n) && (k < m)) {                     // while not done yet
        while ((k < m) && (D.get(d) > H.get(k))) ++k;  // find required knight k
        if (k == m) break;                             // loowater is doomed :S
        gold += H.get(k);                              // pay this amount of gold
        ++d; ++k;                                      // next dragon & knight
      }
      if (d == n) pw.printf("%d\n", gold);             // all dragons are chopped
      else        pw.println("Loowater is doomed!");
    }
    pw.close();
  }
}
