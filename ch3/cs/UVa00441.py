def main(): 
    first = True
    while True:
        x = list(map(int, input().split()))
        k = x[0]
        if k is 0:
            break
        if first:
            first = False
        else:
            print('')
        for a in range(1, k-4):
            for b in range(a+1, k-3):
                for c in range(b+1, k-2):
                    for d in range(c+1, k-1):
                        for e in range(d+1, k):
                            for f in range(e+1, k+1):
                                print('{} {} {} {} {} {}'.format(x[a], x[b], x[c], x[d], x[e], x[f]))

main() 
