MAX_N = 100010
p = 10**9+7

def mod(a, m):
  return ((a % m) + m) % m


def modPow(b, p, m):
  if p == 0:
    return 1
  ans = modPow(b, p//2, m)
  ans = mod(ans*ans, m)
  if p % 2 == 1:
    ans = mod(ans*b, m)
  return ans


def inv(a):
  return modPow(a, p-2, p)


fact = []
invFact = []

def C(n, k):
  global fact, invFact

  if n < k:
    return 0
  return (((fact[n] * inv(fact[k])) % p) * inv(fact[n-k])) % p


def main():
  global fact, invFact

  Fib = [0] * MAX_N
  Fib[0] = 0
  Fib[1] = 1

  for i in range(2, MAX_N):
    Fib[i] = (Fib[i-1] + Fib[i-2]) % p
  print(Fib[100000])

  fact = [0] * MAX_N
  invFact = [0] * MAX_N

  fact[0] = 1
  for i in range(1, MAX_N):
    fact[i] = (fact[i-1]*i)% p

  print(C(100000, 50000))

  Cat = [0] * MAX_N
  Cat[0] = 1
  for n in range(MAX_N-1):
    Cat[n+1] = ((4*n+2)%p * Cat[n]%p * inv(n+2)) % p
  print(Cat[100000])


main()
