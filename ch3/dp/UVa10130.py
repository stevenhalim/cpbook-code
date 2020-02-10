import sys
from functools import lru_cache
sys.setrecursionlimit(2048)

def main():
    tc = int(input())
    for _ in range(tc):
        n = int(input())

        values, weights = [0] * n, [0] * n
        for i in range(n):
            values[i], weights[i] = map(int, input().split())

        @lru_cache(maxsize=None)
        def value(i, w):
            if i == n or w == 0:
                return 0
            if weights[i] > w:
                return value(i + 1, w)
            return max(value(i + 1, w), values[i] + value(i + 1, w - weights[i]))

        groups, total = int(input()), 0
        for _ in range(groups):
            mw = int(input())
            total += value(0, mw)
        print(total)

if __name__ == '__main__':
    main()
