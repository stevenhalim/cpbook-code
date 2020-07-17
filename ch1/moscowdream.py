a, b, c, n = map(int, input().split())
print("YES" if ((a >= 1) and (b >= 1) and (c >= 1) and (a+b+c >= n) and (n >= 3)) else "NO");
