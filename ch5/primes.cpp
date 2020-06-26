#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef map<int, int> mii;

ll _sieve_size;
bitset<10000010> bs;                             // 10^7 is the rough limit
vll primes;                                      // compact list of primes


// first part

void sieve(ll upperbound) {                      // range = [0..upperbound]
  _sieve_size = upperbound+1;                    // to include upperbound
  bs.set(); bs[0] = bs[1] = 0;                   // all 1s except index 0+1
  for (ll i = 2; i < _sieve_size; ++i) if (bs[i]) {
    // cross out multiples of i starting from i*i
    for (ll j = i*i; j < _sieve_size; j += i) bs[j] = 0;
    primes.push_back(i);                         // add prime i to the list
  }
}

bool isPrime(ll N) {                             // good enough prime test
  if (N <= _sieve_size) return bs[N];            // O(1) for small primes
  for (int i = 0; (i < primes.size()) && (primes[i]*primes[i] <= N); ++i)
    if (N%primes[i] == 0)
      return false;
  return true;                                   // slow if N = large prime
} // note: only work for N <= (last prime in vi primes)^2

// second part

vi primeFactors(ll N) {                          // pre-condition, N >= 1
  vi factors;
  ll PF_idx = 0, PF = primes[PF_idx];            // call sieve() before
  while (PF*PF <= N) {                           // stop at sqrt(N)
    while (N%PF == 0) { N /= PF; factors.push_back(PF); } // remove PF
    PF = primes[++PF_idx];                       // only consider primes!
  }
  if (N != 1) factors.push_back(N);              // input N is a prime
  return factors;
}

// third part

ll numPF(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
  while (PF*PF <= N) {
    while (N%PF == 0) { N /= PF; ++ans; }
    PF = primes[++PF_idx];
  }
  return ans + (N != 1);
}

ll numDiffPF(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
  while (PF*PF <= N) {
    if (N%PF == 0) ++ans;                        // count this pf only once
    while (N%PF == 0) N /= PF;
    PF = primes[++PF_idx];
  }
  return ans + (N != 1);
}

ll sumPF(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
  while (PF*PF <= N) {
    while (N%PF == 0) { N /= PF; ans += PF; }
    PF = primes[++PF_idx];
  }
  return ans + (N != 1) * N;
}

ll numDiv(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 1;   // start from ans = 1
  while (PF*PF <= N) {
    ll power = 0;                                // count the power
    while (N%PF == 0) { N /= PF; ++power; }
    ans *= (power+1);                            // follow the formula
    PF = primes[++PF_idx];
  }
  return (N != 1) ? 2*ans : ans;                 // last factor = N^1
}

ll sumDiv(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 1;  // start from ans = 1
  while (PF*PF <= N) {
    ll multiplier = PF, total = 1;
    while (N%PF == 0) {
      N /= PF;
      total += multiplier;
      multiplier *= PF;
    }
    ans *= total;                                // total for this PF
    PF = primes[++PF_idx];
  }
  if (N != 1) ans *= (N+1);                      // N^2-1/N-1 = N+1
  return ans;
}

ll EulerPhi(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = N;   // start from ans = N
  while (PF*PF <= N) {
    if (N%PF == 0) ans -= ans / PF;              // only count unique factor
    while (N%PF == 0) N /= PF;
    PF = primes[++PF_idx];
  }
  return (N != 1) ? ans - ans/N : ans;           // last factor
}

int main() {
  // first part: the Sieve of Eratosthenes
  sieve(10000000);                               // up to 10^7 (<1s)
  printf("%lld\n", primes.back());               // primes.back() = 9999991
  for (int i = primes.back()+1; ; ++i)
    if (isPrime(i)) {
      printf("The next prime beyond the last prime generated is %d\n", i);
      break;
    }
  printf("%d\n", isPrime((1LL<<31)-1));          // 8th Mersenne prime
  printf("%d\n", isPrime(136117223861LL));       // 104729*1299709

  // second part: prime factors
  vi r = primeFactors((1LL<<31)-1);              // slowest, Mersenne prime
  for (auto &pf : r)
    printf("> %d\n", pf);
  r = primeFactors(136117223861LL);              // slow, large prime
  for (auto &pf : r)
    printf("> %d\n", pf);                        // 104729*1299709
  r = primeFactors(142391208960LL);              // faster, large composite
  for (auto &pf : r)
    printf("> %d\n", pf);                        // 2^10*3^4*5*7^4*11*13
  r = primeFactors(99999820000081LL);            // the limit: 9999991^2
  for (auto &pf : r)
    printf("> %d\n", pf);
  printf("\n");

  // r = primeFactors(100000380000361LL);        // error, beyond 9999991^2
  // for (auto &pf : r) printf("> %d\n", pf);
  // printf("\n");
  
  // third part: functions involving prime factors
  printf("numPF(%d) = %lld\n", 60, numPF(60));   // 2^2 * 3^1 * 5^1 => 4
  printf("numDiffPF(%d) = %lld\n", 60, numDiffPF(60)); // 2^2 * 3^1 * 5^1 => 3
  printf("sumPF(%d) = %lld\n", 60, sumPF(60));   // 2^2 * 3^1 * 5^1 => 2 + 2 + 3 + 5 = 12
  printf("numDiv(%d) = %lld\n", 60, numDiv(60)); // 1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30, 60, 12 divisors
  printf("sumDiv(%d) = %lld\n", 60, sumDiv(60)); // The summation of 12 divisors above is 168
  printf("EulerPhi(%d) = %lld\n", 36, EulerPhi(36)); // 12 integers < 36 are relatively prime with 36
  printf("\n");

  // special cases when N is a prime number
  printf("numPF(%d) = %lld\n", 7, numPF(7));     // 7^1 => 1
  printf("numDiffPF(%d) = %lld\n", 7, numDiffPF(7)); // 7^1 = 1
  printf("sumPF(%d) = %lld\n", 7, sumPF(7));     // 7^1 => 7
  printf("numDiv(%d) = %lld\n", 7, numDiv(7));   // 1 and 7, 2 divisors
  printf("sumDiv(%d) = %lld\n", 7, sumDiv(7));   // 1 + 7 = 8
  printf("EulerPhi(%d) = %lld\n", 7, EulerPhi(7)); // 6 integers < 7 are relatively prime with prime number 7

  return 0;
}
