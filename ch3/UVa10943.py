import sys

def main():
    dp = []
    for i in range (110):
        dp.append([0] * 110)

    for i in range (101):
        dp[i][1] = 1

    for j in range (1, 100):
        for i in range (0, 101):
            for split in range (0, 101 - i):
                dp[i + split][j + 1] += dp[i][j]
                dp[i + split][j + 1] %= 1000000


    inputs = sys.stdin.read().splitlines()
    ln = 0

    while True:
        N = int(inputs[ln].split(' ')[0].strip())
        K = int(inputs[ln].split(' ')[1].strip())
        if N == 0 and K == 0:
            break
        ln += 1
        print(dp[N][K])

main()
