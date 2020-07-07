import java.util.*;

class Main { /* UVa 12455 - Bars */
  private static int LSOne(int S) {
    return S & (-S);
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int t = sc.nextInt();
    while (t-- > 0) {
      int X = sc.nextInt();
      int n = sc.nextInt();
      int[] l = new int[n];
      for (int i = 0; i < n; ++i)
        l[i] = sc.nextInt();
      int i;
      for (i = 0; i < (1<<n); ++i) {               // for each subset, O(2^n)
        int sum = 0;
        // for (int j = 0; j < n; ++j)             // check membership, O(n)
        //   if (i & (1<<j))                       // see if bit 'j' is on?
        //     sum += l[j];                        // if yes, process 'j'
        int mask = i;                              // this is now O(k)
        while (mask > 0) {                         // k is the # of on bits
          int two_pow_j = LSOne(mask);             // least significant bit
          int j = (int)(Math.log(two_pow_j)/Math.log(2)); // 2^j = two_pow_j, get j
          sum += l[j];
          mask -= two_pow_j;
        }
        if (sum == X) break;                       // the answer is found
      }
      System.out.println(i < (1<<n) ? "YES" : "NO");
    }
  }
}
