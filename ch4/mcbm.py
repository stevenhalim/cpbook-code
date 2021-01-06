import random

match = []
vis = []
AL = []

def Aug(L):
    global match, vis, AL

    if vis[L]:
        return 0
    vis[L] = 1
    for R in AL[L]:
        if match[R] == -1 or Aug(match[R]):
        match[R] = L
        return 1
    return 0

def main():
    global match, vis, AL

    V = 5
    Vleft = 3
    AL = [list() for _ in range(V)]
    AL[1] = [3, 4]
    AL[2] = [3]

    freeV = set()
    for L in range(Vleft):
        freeV.add(L)
    match = [-1] * V
    MCBM = 0

    for L in range(Vleft):
        candidates = []
        for R in AL[L]:
            if match[R] == -1:
                candidates.append(R)
        if len(candidates) > 0:
            MCBM += 1
            freeV.remove(L)
            a = random.randrange(len(candidates))
            match[candidates[a]] = L
 
    for f in freeV:
        vis = [0] * Vleft
        MCBM += Aug(f)

    print('Found %d matchings' % MCBM)

main()
