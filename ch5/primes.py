import sys

_sieve_size = 0
bs = []
primes = []


def sieve(upperbound):
  global _sieve_size, bs, primes

  _sieve_size = upperbound+1
  bs = [True] * 10000010
  bs[0] = bs[1] = False
  for i in range(2, _sieve_size):
    if bs[i]:
      for j in range(i*i, _sieve_size, i):
        bs[j] = False
      primes.append(i)


def isPrime(N):
  global _sieve_size, primes
  if N <= _sieve_size:
    return bs[N]
  for p in primes:
    if p * p > N:
      break
    if N % p == 0:
      return False
  return True


def primeFactors(N):
  global primes

  factors = []
  PF_idx = 0
  PF = primes[PF_idx]

  while PF * PF <= N:
    while N % PF == 0:
      N //= PF
      factors.append(PF)
    PF_idx += 1
    PF = primes[PF_idx]
  if N != 1:
    factors.append(N)

  return factors


def numPF(N):
  global primes

  PF_idx = 0
  PF = primes[PF_idx]
  ans = 0

  while PF * PF <= N:
    while N % PF == 0:
      N //= PF
      ans += 1
    PF_idx += 1
    PF = primes[PF_idx]
  if N != 1:
    ans += 1

  return ans


def numDiffPF(N):
  global primes

  PF_idx = 0
  PF = primes[PF_idx]
  ans = 0

  while PF * PF <= N:
    if N % PF == 0:
      ans += 1
    while N % PF == 0:
      N //= PF
    PF_idx += 1
    PF = primes[PF_idx]
  if N != 1:
    ans += 1

  return ans


def sumPF(N):
  global primes

  PF_idx = 0
  PF = primes[PF_idx]
  ans = 0

  while PF * PF <= N:
    while N % PF == 0:
      N //= PF
      ans += PF
    PF_idx += 1
    PF = primes[PF_idx]
  if N != 1:
    ans += N

  return ans


def numDiv(N):
  global primes

  PF_idx = 0
  PF = primes[PF_idx]
  ans = 1

  while PF * PF <= N:
    power = 0
    while N % PF == 0:
      N //= PF
      power += 1
    ans = ans * (power + 1)
    PF_idx += 1
    PF = primes[PF_idx]

  if N != 1:
    return 2 * ans
  else:
    return ans


def sumDiv(N):
  global primes

  PF_idx = 0
  PF = primes[PF_idx]
  ans = 1

  while PF * PF <= N:
    multiplier = PF
    total = 1
    while N % PF == 0:
      N //= PF
      total += multiplier
      multiplier *= PF
    ans *= total
    PF_idx += 1
    PF = primes[PF_idx]
  if N != 1:
    ans *= N+1

  return ans


def EulerPhi(N):
  global primes

  PF_idx = 0
  PF = primes[PF_idx]
  ans = N

  while PF * PF <= N:
    if N % PF == 0:
      ans -= ans // PF
    while N % PF == 0:
      N //= PF
    PF_idx += 1
    PF = primes[PF_idx]
  if N != 1:
    ans -= ans // N

  return ans


def main():
  global primes

  sieve(10000000)
  print(primes[-1])

  i = primes[-1]+1
  while True:
    if isPrime(i):
      print('The next prime beyond the last prime generated is %d' % i)
      break
    i += 1
  print(isPrime(2**31-1))
  print(isPrime(136117223861))

  r = primeFactors(2**31-1)
  for pf in r:
    print('>', pf)
  r = primeFactors(136117223861)
  for pf in r:
    print('>', pf)
  r = primeFactors(142391208960)
  for pf in r:
    print('>', pf)
  # r = primeFactors(99999820000081)      # 'error'
  # for pf in r:
  #   print('>', pf)
  print()

  print('numPF(%d) = %d' % (60, numPF(60)))
  print('numDiffPF(%d) = %d' % (60, numDiffPF(60)))
  print('sumPF(%d) = %d' % (60, sumPF(60)))
  print('numDiv(%d) = %d' % (60, numDiv(60)))
  print('sumDiv(%d) = %d' % (60, sumDiv(60)))
  print('EulerPhi(%d) = %d' % (36, EulerPhi(36)))
  print();

  print('numPF(%d) = %d' % (7, numPF(7)))
  print('numDiffPF(%d) = %d' % (7, numDiffPF(7)))
  print('sumPF(%d) = %d' % (7, sumPF(7)))
  print('numDiv(%d) = %d' % (7, numDiv(7)))
  print('sumDiv(%d) = %d' % (7, sumDiv(7)))
  print('EulerPhi(%d) = %d' % (7, EulerPhi(7)))


main()
