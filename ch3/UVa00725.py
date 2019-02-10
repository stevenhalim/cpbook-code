def main():
    first = True
    N = int(input())
    while not N == 0:
        if not first:
            print()
        first = False
        noSolution = True
        for fghij in range(1234, 98765//N + 1): # faster if we check from 1234 to 98765/n instead to 98765
            abcde = fghij * N   # this way, abcde and fghij are at most 5 digits
            used = (fghij < 10000) # if digit f = 0, then we have to flag it
            tmp = abcde
            while tmp:
                used |= (1 << (tmp % 10))
                tmp //= 10
            tmp = fghij
            while tmp:
                used |= (1 << (tmp % 10))
                tmp //= 10
            if used == (1<<10)-1:       # if all digits are used, print it
                print("{:05d} / {:05d} = {}".format(abcde, fghij, N))
                noSolution = False
        if noSolution:
            print("There are no solutions for {}.".format(N))
        N = int(input())
main() 
