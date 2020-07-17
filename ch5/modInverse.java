class modInverse {
  private static int mod(int a, int m) {         // returns a (mod m)
    return ((a%m) + m) % m;                      // ensure positive answer
  }

  private static int modPow(int b, int p, int m) { // assume 0 <= b < m
    if (p == 0) return 1;
    int ans = modPow(b, p/2, m);                 // this is O(log p)
    ans = mod(ans*ans, m);                       // double it first
    if ((p&1) == 1) ans = mod(ans*b, m);         // *b if p is odd
    return ans;                                  // ans always in [0..m-1]
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

  public static void main(String[] args) {
    // Fermat's little theorem, b^-1 = b^{m-2} (mod m)
    System.out.println((27%7 * modPow(3, 5, 7)) % 7);  // example 1, output 2
    System.out.println((27%7 * modPow(4, 5, 7)) % 7);  // example 2, output 5
    System.out.println((520%18 * modPow(25, 16, 18)) % 18); // example 3, wrong answer, doesn't output 10 because 18 is not a prime

    // Using extEuclid
    System.out.println((27%7 * modInverse(3, 7)) % 7); // example 1, output 2
    System.out.println((27%7 * modInverse(4, 7)) % 7); // example 2, output 5
    System.out.println((520%18 * modInverse(25, 18)) % 18); // example 3, output 10
  }
}
