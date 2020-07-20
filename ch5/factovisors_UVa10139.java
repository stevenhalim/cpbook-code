import java.util.*;

class factovisors_UVa10139 { /* Factovisors */
  private static int vp(int p, int n) {            // Legendre's formula
    int ans = 0;
    for (int pi = p; pi <= n; pi *= p)
      ans += n/pi;                                 // floor by default
    return ans;
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNext()) {
      int n = sc.nextInt(), m = sc.nextInt();
      Boolean possible;
           if (m == 0) possible = false;           // special case
      else if (m <= n) possible = true;            // always true
      else {                                       // factorize m
        HashMap<Integer, Integer> factor_m = new HashMap<>(); // in any order
        int temp = m;
        int PF = 2;
        while ((temp > 1) && ((long)PF*PF <= m)) {
          int freq = 0;
          while (temp%PF == 0) {                   // take out this factor
            ++freq;
            temp /= PF;
          }
          if (freq > 0) factor_m.put(PF, freq);
          ++PF;                                    // next factor
        }
        if (temp > 1) factor_m.put(temp, 1);

        possible = true;
        for (Map.Entry<Integer, Integer> entry : factor_m.entrySet()) // for each p^e in m
          if (vp(entry.getKey(), n) < entry.getValue()) { // has support in n!?
            possible = false;                      // ups, not enough
            break;
          }
      }

      System.out.printf("%d %s %d!\n", m, possible ? "divides" : "does not divide", n);
    }
  }
}
