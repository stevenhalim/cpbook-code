import sys

def main():
    inputs = sys.stdin.read().splitlines()
    ln = 0
    while True:
        N,B = map(int, inputs[ln].split())
        if N == -1 and B == -1: break
        ln += 1
        
        A = []
        for _ in range(N):
            A.append(int(inputs[ln]))
            ln += 1
        ln += 1

        A = tuple(A)

        L = 1
        R = max(A)
        ans = R

        # is x a feasible answer?
        def can(x):
          need = 0
          for a in A:
            need += (a + x - 1) // x
          return need <= B

        # binary search the answer
        while L <= R:
          m = (L + R) // 2
          if can(m):
            ans = m
            R = m - 1
          else:
            L = m + 1

        print(ans)

main()
