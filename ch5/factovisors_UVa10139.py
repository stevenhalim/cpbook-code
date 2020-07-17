import sys

def vp(p, n):                                     # Legendre's formula
    ans = 0
    pi = p
    while pi <= n:
        ans += n//pi                              # floor by default
        pi *= p
    return ans

def main():
    for line in sys.stdin:
        n,m = map(int, line.split())
        possible = True
        if m == 0:                                # special case
            possible = False
        elif m <= n:                              # always true
            possible = True
        else:                                     # factorize m
            factor_m = dict();                    # in any order
            temp = m
            PF = 2
            while temp > 1 and PF*PF <= m:
                freq = 0
                while temp%PF == 0:               # take out this factor
                    freq += 1
                    temp /= PF
                if freq > 0:
                    factor_m[PF] = freq
                PF += 1                           # next factor
            if temp > 1:
                factor_m[temp] = 1

            possible = True
            for p, e in factor_m.items():         # for each p^e in m
               if vp(p, n) < e:                   # has support in n!?
                   possible = False               # ups, not enough
                   break

        print("{} {} {}!".format(m, ("divides" if possible else "does not divide"), n))

main()
