def main():
    first = True
    while True:
        n = int(input())
        if n is 0:
            break
        if not first:
            print('')
        first = False
        noSolution = True
        for fghij in range(1234, (98765//n) + 1):
            abcde = fghij * n
            used = (fghij < 10000)
            tmp = abcde
            while tmp is not 0:
                used |= 1<<(tmp%10)
                tmp //= 10
            tmp = fghij
            while tmp is not 0:
                used |= 1<<(tmp%10)
                tmp //= 10
            if used == (1<<10) - 1:
                print('{:05} / {:05} = {}'.format(abcde, fghij, n))
                noSolution = False
        if noSolution:
            print('There are no solutions for {}.'.format(n))

main()
