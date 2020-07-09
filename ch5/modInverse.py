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


def extEuclid(a, b):
  xx, yy = 0, 1
  x, y = 1, 0
  while b != 0:
    q = a//b
    a, b = b, a%b
    x, xx = xx, x-q*xx
    y, yy = yy, y-q*yy
  return a, x, y


def modInverse(b, m):
  d, x, y = extEuclid(b, m)
  if d != 1:
    return -1
  return mod(x, m)


def main():
  print('%d' % ((27%7 * modPow(3, 5, 7)) % 7))
  print('%d' % ((27%7 * modPow(4, 5, 7)) % 7))
  print('%d' % ((520%18 * modPow(25, 16, 18)) % 18))

  print('%d' % ((27%7 * modInverse(3, 7)) % 7))
  print('%d' % ((27%7 * modInverse(4, 7)) % 7))
  print('%d' % ((520%18 * modInverse(25, 18)) % 18))


main()
