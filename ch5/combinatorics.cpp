#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 100010;
const int p = 1e9+7;                             // p is a prime > MAX_N

ll modPow(ll base, ll p, int m) {                // O(log p)
       if (p == 0) return 1;
  else if (p == 1) return base%m;
  else {
    ll ans = modPow(base, p/2, m)%m;
    ans = (ans*ans)%m;
    if (p&1) ans = (ans*base)%m;                 // if p is odd
    return ans;
  }
}

ll inv(ll a) {                                   // Fermat's little theorem
  return modPow(a, p-2, p);                      // modPow in Section 5.8
}                                                // that runs in O(log p)

ll fact[MAX_N], invFact[MAX_N];

ll C(ll n, ll k) {                               // O(log p)
  if (n < k) return 0;                           // clearly
  return (((fact[n] * inv(fact[k])) % p) * inv(fact[n-k])) % p;
  // return (((fact[n] * invFact[k]) % p) * invFact[n-k]) % p;
}

ll Fib[MAX_N], Cat[MAX_N];

int main() {
  Fib[0] = 0;                                    // the first
  Fib[1] = 1;                                    // two terms of Fibonacci
  for (int i = 2; i < MAX_N; ++i)                // O(MAX_N) pre-processing
    Fib[i] = (Fib[i-1] + Fib[i-2]) % p;          // Fib[i] in [0..p-1]
  cout << Fib[100000] << "\n";                   // the answer is 911435502

  fact[0] = 1;
  for (int i = 1; i < MAX_N; ++i)                // O(MAX_N) pre-processing
    fact[i] = (fact[i-1]*i)% p;                  // fact[i] in [0..p-1]

  // invFact[MAX_N-1] = inv(fact[MAX_N-1]);         // one O(log p)
  // for (int i = MAX_N-2; i >= 0; --i)             // O(MAX_N) pre-processing
  //   invFact[i] = (invFact[i+1]*(i+1)) % p;
  cout << C(100000, 50000) << "\n";              // the answer is 149033233

  Cat[0] = 1;
  for (int n = 0; n < MAX_N-1; ++n)              // O(MAX_N * log p)
    Cat[n+1] = ((4*n+2)%p * Cat[n]%p * inv(n+2)) % p;
  cout << Cat[100000] << endl;                   // the answer is 945729344

  return 0;
}
