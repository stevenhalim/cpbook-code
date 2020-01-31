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

def value(id, w):
    global N, W, V, memo
    if id == N or w == 0:
        return 0
    if memo[id][w] != -1:
        return memo[id][w]
    if W[id] > w:
        memo[id][w] = value(id+1, w)
        return memo[id][w]
    memo[id][w] = max([value(id+1, w), V[id] + value(id+1, w-W[id])])
    return memo[id][w]

def main():
    inp = SamInput()
    T = int(inp.read())
    for _ in range(T):
        global N, W, V, memo
        N = int(inp.read())
#        print("outside, N = ", N)
        memo = []
        for i in range(N+1):
            memoTable = []
            for j in range(40):
                memoTable.append(-1)
            memo.append(memoTable)

        V = [0] * N
        W = [0] * N
        for i in range(N):
            V[i] = int(inp.read())
            W[i] = int(inp.read())

        ans = 0
        G = int(inp.read())
        for _ in range(G):
            MW = int(inp.read())
#            print("MW = ", MW)
            ans += value(0, MW)
        print(ans)

if __name__ == '__main__':
    main()
