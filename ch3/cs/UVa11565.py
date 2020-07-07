def main():
    N = int(input())
    for _ in range(N):
        A,B,C = map(int, input().split())
        sol = False
        for x in range(-22, 23):
            if sol:
                break
            if x*x <= C:
                for y in range(-100, 101):
                    if sol:
                        break
                    if y != x and x*x + y*y <= C:
                        for z in range(-100, 101):
                            if sol:
                                break
                            if z != x and z != y and x+y+z == A and x*y*z == B and x*x + y*y + z*z == C:
                                print("{} {} {}".format(x, y, z))
                                sol = True
        if not sol:
            print("No solution.")

main()
