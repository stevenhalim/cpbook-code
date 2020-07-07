import java.util.*;

class heliocentric {
  private static int mod(long a, int m) {        // returns a (mod m)
    return (int)(((a%m) + m) % m);               // ensure positive answer
  }

  private static int[] extEuclid(int a, int b) {
    int xx = 0;
    int yy = 1;
    int x = 1;
    int y = 0;
    while (b > 0) {                              // repeats until b == 0
      int q = a/b;
      int t = b; b = a%b; a = t;
      t = xx; xx = x-q*xx; x = t;
      t = yy; yy = y-q*yy; y = t;
    }
    return new int[] { a, x, y };                // returns [gcd(a, b), x, y]
  }

  private static int modInverse(int b, int m) {  // returns b^(-1) (mod m)
    int[] dxy = extEuclid(b, m);                 // to get b*x + m*y == d
    if (dxy[0] != 1) return -1;                  // to indicate failure
    // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
    return mod(dxy[1], m);
  }

  private static int crt(ArrayList<Integer> r, ArrayList<Integer> m) {
    // m_t = m_0*m_1*...*m_{n-1}
    int mt = 1;
    for (int i = 0; i < m.size(); ++i)
      mt *= m.get(i);
    int x = 0;
    for (int i = 0; i < m.size(); ++i) {
      int a = mod((long)r.get(i) * modInverse(mt/m.get(i), m.get(i)), m.get(i));
      x = mod(x + (long)a * (mt/m.get(i)), mt);
    }
    return x;
  }

  public static void main(String[] args) {
    int caseNo = 0;
    Scanner sc = new Scanner(System.in);
    while (sc.hasNext()) {
      int e = sc.nextInt(), m = sc.nextInt();
      // Chinese Remainder Theorem way
      // x = e (mod 365)
      // x = m (mod 687)
      // 365 and 687 are coprime, mt = 365*687 = 250755
      ArrayList<Integer> orbit = new ArrayList<>() {{ add(365); add(687); }}; // the number of days of earth and mars orbits, respectively, gcd(365, 687) = 1, pairwise coprime
      ArrayList<Integer> r = new ArrayList<>() {{ add(e); add(m); }};
      int x = crt(r, orbit); // at x-th day, earth and mars will align
      int ans = mod(250755-x, 250755); // 250755-x more day, both earth and mars will be at day 0, note that 250755 mod (250755) = 0, i.e., today both planets are on day 0 of their orbits already

      System.out.printf("Case %d: %d\n", ++caseNo, ans);
    }
  }
}
