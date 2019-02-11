def canPlace(r, c):
    for prev in range(c):
        if row[prev] == r or abs(row[prev]-r) == abs(prev-c):
            return False
    return True

def backtrack(c):
    global lineCounter
    if c == 8 and row[b] == a:
        lineCounter += 1
        print("%2d     " % lineCounter, *[i+1 for i in row])
        return
    for r in range(8):
        if c == b and r != a:
            continue
        if canPlace(r, c):
            row[c] = r
            backtrack(c+1)

for tc in range(int(input())):
    if tc > 0:
        print()
    input()
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    row = [0] * 8
    lineCounter = 0
    print("SOLN       COLUMN")
    print(" #      1 2 3 4 5 6 7 8\n")
    backtrack(0)
