def main():
    while True:
        n,m = map(int, input().split())
        if n==0 and m==0:
            break
        D = [9] * n
        H = [0] * m
        for d in range(n):
            D[d] = int(input())
        for k in range(m):
            H[k] = int(input())
        D.sort()                                 # sorting is an important
        H.sort()                                 # pre-processing step
        gold = 0
        d = 0
        k = 0                                    # both arrays are sorted
        while d < n and k < m:                   # while not done yet
            while k < m and D[d] > H[k]:
                k += 1                           # find required knight k
            if k == m:
                break                            # loowater is doomed :S
            gold += H[k]                         # pay this amount of gold
            d += 1                               # next dragon
            k += 1                               # next knight
        if d == n:
            print("{}".format(gold))             # all dragons are chopped
        else:
            print("Loowater is doomed!")

main()
