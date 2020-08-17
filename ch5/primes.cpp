#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef map<int, int> mii;

ll _sieve_size;
bitset<10000010> bs;                             // 10^7 is the rough limit
vll p;                                           // compact list of primes

void sieve(ll upperbound) {                      // range = [0..upperbound]
  _sieve_size = upperbound+1;                    // to include upperbound
  bs.set();                                      // all 1s
  bs[0] = bs[1] = 0;                             // except index 0+1
  for (ll i = 2; i < _sieve_size; ++i) if (bs[i]) {
    // cross out multiples of i starting from i*i
    for (ll j = i*i; j < _sieve_size; j += i) bs[j] = 0;
    p.push_back(i);                              // add prime i to the list
  }
}

bool isPrime(ll N) {                             // good enough prime test
  if (N < _sieve_size) return bs[N];             // O(1) for small primes
  for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
    if (N%p[i] == 0)
      return false;
  return true;                                   // slow if N = large prime
} // note: only guaranteed to work for N <= (last prime in vll p)^2

// second part

vll primeFactors(ll N) {                         // pre-condition, N >= 1
  vll factors;
  for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
    while (N%p[i] == 0) {                        // found a prime for N
      N /= p[i];                                 // remove it from N
      factors.push_back(p[i]);
    }
  if (N != 1) factors.push_back(N);              // remaining N is a prime
  return factors;
}

// third part

int numPF(ll N) {
  int ans = 0;
  for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
    while (N%p[i] == 0) { N /= p[i]; ++ans; }
  return ans + (N != 1);
}

int numDiffPF(ll N) {
  int ans = 0;
  for (int i = 0; i < p.size() && p[i]*p[i] <= N; ++i) {
    if (N%p[i] == 0) ++ans;                      // count this prime factor
    while (N%p[i] == 0) N /= p[i];               // only once
  }
  if (N != 1) ++ans;
  return ans;
}

ll sumPF(ll N) {
  ll ans = 0;
  for (int i = 0; i < p.size() && p[i]*p[i] <= N; ++i)
    while (N%p[i] == 0) { N /= p[i]; ans += p[i]; }
  if (N != 1) ans += N;
  return ans;
}

int numDiv(ll N) {
  int ans = 1;                                   // start from ans = 1
  for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
    int power = 0;                               // count the power
    while (N%p[i] == 0) { N /= p[i]; ++power; }
    ans *= power+1;                              // follow the formula
  }
  return (N != 1) ? 2*ans : ans;                 // last factor = N^1
}

ll sumDiv(ll N) {
  ll ans = 1;                                    // start from ans = 1
  for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
    ll multiplier = p[i], total = 1;
    while (N%p[i] == 0) {
      N /= p[i];
      total += multiplier;
      multiplier *= p[i];
    }                                            // total for
    ans *= total;                                // this prime factor
  }
  if (N != 1) ans *= (N+1);                      // N^2-1/N-1 = N+1
  return ans;
}

ll EulerPhi(ll N) {
  ll ans = N;                                    // start from ans = N
  for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
    if (N%p[i] == 0) ans -= ans/p[i];            // count unique
    while (N%p[i] == 0) N /= p[i];               // prime factor
  }
  if (N != 1) ans -= ans/N;                      // last factor
  return ans;
}

int main() {
  // first part: the Sieve of Eratosthenes
  sieve(10000000);                               // up to 10^7 (<1s)
  printf("%lld\n", p.back());               // primes.back() = 9999991
  for (int i = p.back()+1; ; ++i)
    if (isPrime(i)) {
      printf("The next prime beyond the last prime generated is %d\n", i);
      break;
    }
  printf("%d\n", isPrime((1LL<<31)-1));          // 8th Mersenne prime
  printf("%d\n", isPrime(136117223861LL));       // 104729*1299709
  printf("\n");

  // second part: prime factors
<<<<<<< HEAD
  vll r;

  r = primeFactors((1LL<<31)-1);                 // Mersenne prime
  printf("%lld\n", (1LL<<31)-1);
  for (auto &pf : r) printf("> %lld\n", pf);
  printf("\n");

  r = primeFactors(136117223861LL);              // large prime factors
  printf("%lld\n", 136117223861LL);
  for (auto &pf : r) printf("> %lld\n", pf);     // 104729*1299709
  printf("\n");

  r = primeFactors(5000000035LL);                // large prime factors
  printf("%lld\n", 5000000035LL);
  for (auto &pf : r) printf("> %lld\n", pf);     // 5*1000000007
  printf("\n");

  r = primeFactors(142391208960LL);              // large composite
  printf("%lld\n", 142391208960LL);
  for (auto &pf : r) printf("> %lld\n", pf);     // 2^10*3^4*5*7^4*11*13
  printf("\n");

  r = primeFactors(100000380000361LL);           // 10000019^2
  printf("%lld\n", 100000380000361LL);
  for (auto &pf : r) printf("> %lld\n", pf);     // fail to factor! (why?)
  printf("\n");

  
=======
  vi r = primeFactors((1LL<<31)-1);              // slowest, Mersenne prime
  for (auto &pf : r)
    printf("> %d\n", pf);
  r = primeFactors(136117223861LL);              // slow, large prime
  for (auto &pf : r)
    printf("> %d\n", pf);                        // 104729*1299709
  r = primeFactors(142391208960LL);              // faster, large composite
  for (auto &pf : r)
    printf("> %d\n", pf);                        // 2^10*3^4*5*7^4*11*13
  // r = primeFactors(99999820000081LL);            // the limit: 9999991^2
  // for (auto &pf : r)
  //   printf("> %d\n", pf);
  // printf("\n");

  r = primeFactors(9999973LL*9999973LL);         // 9999973^2, the limit
  for (auto &pf : r)
    printf("> %d\n", pf);
  printf("\n");
  // r = primeFactors(9999991LL*9999991LL);         // 9999991^2, first crash
  // for (auto &pf : r)
  //   printf("> %d\n", pf);
  // printf("\n");

>>>>>>> master
  // third part: functions involving prime factors
  printf("numPF(%d) = %d\n", 60, numPF(60));   // 2^2 * 3^1 * 5^1 => 4
  printf("numDiffPF(%d) = %d\n", 60, numDiffPF(60)); // 2^2 * 3^1 * 5^1 => 3
  printf("sumPF(%d) = %lld\n", 60, sumPF(60));   // 2^2 * 3^1 * 5^1 => 2 + 2 + 3 + 5 = 12
  printf("numDiv(%d) = %d\n", 60, numDiv(60)); // 1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30, 60, 12 divisors
  printf("sumDiv(%d) = %lld\n", 60, sumDiv(60)); // The summation of 12 divisors above is 168
  printf("EulerPhi(%d) = %lld\n", 36, EulerPhi(36)); // 12 integers < 36 are relatively prime with 36
  printf("\n");

  // special cases when N is a prime number
  printf("numPF(%d) = %d\n", 7, numPF(7));     // 7^1 => 1
  printf("numDiffPF(%d) = %d\n", 7, numDiffPF(7)); // 7^1 = 1
  printf("sumPF(%d) = %lld\n", 7, sumPF(7));     // 7^1 => 7
  printf("numDiv(%d) = %d\n", 7, numDiv(7));   // 1 and 7, 2 divisors
  printf("sumDiv(%d) = %lld\n", 7, sumDiv(7));   // 1 + 7 = 8
  printf("EulerPhi(%d) = %lld\n", 7, EulerPhi(7)); // 6 integers < 7 are relatively prime with prime number 7

  return 0;
}
