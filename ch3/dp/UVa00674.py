import sys

N = 5
coinValue = [1, 5, 10, 25, 50]
memo = []

def ways(coin_type, value):
    if value == 0:
        return 1
    if value < 0 or coin_type == 5:
        return 0
    if memo[coin_type][value] == -1:
        memo[coin_type][value] = ways(coin_type+1, value) + ways(coin_type, value - coinValue[coin_type])
    return memo[coin_type][value]

def main():
    for i in range(6):
        memoTable = [-1] * 40
        memo.append(memoTable)
    for money in sys.stdin: # read until EOF
        money = int(money)
        print(ways(0, money))

main()
