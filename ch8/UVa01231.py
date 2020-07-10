if __name__ == '__main__':
  c = int(input())
  for _ in range(c):
    t, h, f = map(int, input().split())

    acorn = [[0] * 2010 for _ in range(2010)]
    dp = [0] * 2010

    for i in range(t):
      tkn = list(map(int, input().split()))
      a = tkn[0]
      for j in range(a):
        acorn[i][tkn[j+1]] += 1

    for tree in range(t):
      dp[h] = max(dp[h], acorn[tree][h])
    for height in range(h-1, -1, -1):
      for tree in range(t):
        acorn[tree][height] += \
          max(acorn[tree][height+1], dp[height+f] if height+f <= h else 0)
        dp[height] = max(dp[height], acorn[tree][height])
    print(dp[0])
