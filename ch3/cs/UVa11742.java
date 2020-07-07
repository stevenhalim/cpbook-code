import java.util.*;

class Main { /* UVa 11742 - Social Constraints  */
  private static int n, m, ans;
  private static int[] a, b, c, p;

  private static void permute(int i, int mask) { // try all possible O(n!) permutations, the largest nput 8! = 40320
    if (mask == (1<<n)-1) { // we found one permutation
      Boolean all_ok = true; // check the given social constraints based on 'p' in O(m)
      for (int j = 0; (j < m) && all_ok; ++j) { // check all constraints, max 20, each check 8 = 160
        int pos_a = p[a[j]], pos_b = p[b[j]];
        int d_pos = Math.abs(pos_a-pos_b);
        if (c[j] > 0)
          all_ok = (d_pos <= c[j]);           // positive, at most  c[j]
        else
          all_ok = (d_pos >= Math.abs(c[j])); // negative, at least c[j]
      }
      if (all_ok) ++ans; // all constraints are satisfied by this permutation
    }
    for (int j = 0; j < n; ++j)
      if ((mask & (1<<j)) == 0) { // still available
        p[i] = j;
        permute(i+1, mask | (1<<j));
      }
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (true) {
      n = sc.nextInt(); m = sc.nextInt();
      if ((n == 0) && (m == 0)) break;
      a = new int[m]; b = new int[m]; c = new int[m];
      for (int j = 0; j < m; ++j) {
        a[j] = sc.nextInt();
        b[j] = sc.nextInt();
        c[j] = sc.nextInt();
      }
      ans = 0;
      p = new int[n];
      permute(0, 0); // the overall time complexity is thus O(m * n!)
      System.out.println(ans); // overall complexity = 160 * 40320 = 6M, doable
    }
  }
}
