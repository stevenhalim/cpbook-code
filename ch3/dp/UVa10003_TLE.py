import sys
from functools import lru_cache
sys.setrecursionlimit(5000)

def main():
    inputs = sys.stdin.read().splitlines()        # unfortunately still TLE even if I use this
    outputs = []
    ln = 0
    while True:
        l = int(inputs[ln])
        ln += 1
        if l == 0: break
        n = int(inputs[ln])
        ln += 1
        A = list(map(int, inputs[ln].split()))
        ln += 1
        A.insert(0, 0)
        A.insert(len(A), l)

        @lru_cache(maxsize=None)
        def cut(left, right):
            if left+1 == right: return 0
            ans = 2e9
            for i in range(left+1, right):
                ans = min(ans, cut(left, i) + cut(i, right) + (A[right]-A[left]))
            return ans

        outputs.append("The minimum cutting is {}.".format(cut(0, n+1))) # start with left = 0 and right = n+1

    sys.stdout.write('\n'.join(outputs))

main()
