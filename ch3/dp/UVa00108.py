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

A = []

def main(): #O(n^3) 1D DP + greedy (Kadane's) solution
    inp = SamInput()

    for i in range(110): #setting up the dp table
        dptable = []
        for j in range(110):
            dptable.append(-1)
        A.append(dptable)
    n = int(inp.read()) #the dimension of input square matrix
    for i in range(n):
        for j in range(n):
            A[i][j] = int(inp.read())
            if j > 0:
                A[i][j] += A[i][j-1] # only add columns of this row i
    maxSubRect = -127 * 100 * 100 # lowest possible value
    for l in range(n):
        for r in range(l, n):
            subRect = 0
            for row in range(n):
                if l > 0: #max 1D Range Sum on columns in this row
                    subRect += A[row][r] - A[row][l-1]
                else:
                    subRect += A[row][r]
                if subRect < 0: #greedy, restart if running sum < 0
                    subRect = 0
                maxSubRect = max(maxSubRect, subRect) #Kadane's algo in rows
    print(maxSubRect)


main()
