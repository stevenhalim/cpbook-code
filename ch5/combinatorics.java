class combinatorics {
  private static final int MAX_N = 100010;
  private static final int p = 1000000007;       // p is a prime > MAX_N

  private static long mod(long a, int m) {       // returns a (mod m)
    return ((a%m) + m) % m;                      // ensure positive answer
  }

  private static long modPow(long b, int p, int m) { // assume 0 <= b < m
    if (p == 0) return 1;
    long ans = modPow(b, p/2, m);                // this is O(log p)
    ans = mod(ans*ans, m);                       // double it first
    if ((p&1) == 1) ans = mod(ans*b, m);         // *b if p is odd
    return ans;                                  // ans always in [0..m-1]
  }

  private static long inv(long a) {              // Fermat's little theorem
    return modPow(a, p-2, p);                    // modPow in Section 5.8
  }                                              // that runs in O(log p)

  private static long[] fact = new long[MAX_N], invFact = new long[MAX_N];

  private static long C(int n, int k) {          // O(log p)
    if (n < k) return 0;                         // clearly
    return (((fact[n] * inv(fact[k])) % p) * inv(fact[n-k])) % p;
    // return (((fact[n] * invFact[k]) % p) * invFact[n-k]) % p; // O(1)
  }

  private static long[] Fib = new long[MAX_N], Cat = new long[MAX_N];

  public static void main(String[] args) {
    Fib[0] = 0;                                  // the first
    Fib[1] = 1;                                  // two terms of Fibonacci
    for (int i = 2; i < MAX_N; ++i)              // O(MAX_N) pre-processing
      Fib[i] = (Fib[i-1] + Fib[i-2]) % p;        // Fib[i] in [0..p-1]
    System.out.println(Fib[100000]);             // the answer is 911435502

    fact[0] = 1;
    for (int i = 1; i < MAX_N; ++i)              // O(MAX_N) pre-processing
      fact[i] = (fact[i-1]*i)% p;                // fact[i] in [0..p-1]

    // invFact[MAX_N-1] = inv(fact[MAX_N-1]);       // one O(log p)
    // for (int i = MAX_N-2; i >= 0; --i)           // O(MAX_N) pre-processing
    //   invFact[i] = (invFact[i+1]*(i+1)) % p;
    System.out.println(C(100000, 50000));        // the answer is 149033233

    Cat[0] = 1;
    for (int n = 0; n < MAX_N-1; ++n)            // O(MAX_N * log p)
      Cat[n+1] = ((4*n+2)%p * Cat[n]%p * inv(n+2)) % p;
    System.out.println(Cat[100000]);             // the answer is 945729344
  }
}
