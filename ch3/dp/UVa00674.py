import sys

# input
class SamInput(object):
    def __init__(self):
        self.inp = []
        for i in sys.stdin:
            i = i.replace("\n", "")
            j = list(i.split())
            self.inp.append(j)

    def readln(self):
        if len(self.inp) == 0:
            return False
        else:
            return str.join(" ", self.inp.pop(0))

    def read(self):
        if len(self.inp) == 0:
            return False
        while len(self.inp[0]) == 0:
            self.inp.pop(0)
            if len(self.inp) == 0:
                return False
        return self.inp[0].pop(0)


# How to use:
# 1) copy line 1-25
# 2) declare variable as SamInput()
# Ex: test = SamInput()
# 3) to read one line, use readln
# Ex: newline = test.readln()
# 4) to read one element(splitted by empty line / whitespace), use read
# Ex: newline = test.read()
# 5) remember, all this function will return a string, need to convert to int
# 6) if there is no more element/line, it will return False (boolean object)

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
    inp = SamInput()
    for i in range(6):
        memoTable = []
        for j in range(7500):
            memoTable.append(-1)
        memo.append(memoTable)
    while True:
        money = inp.read()
        #my input will return False when it is arrived at the end of input
        if not money:
            break
        money = int(money)
        print(ways(0, money))

if __name__ == '__main__':
    main()
