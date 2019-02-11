import sys

# input
class InputHelper(object):
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

def LSOne(S):
    return (-S) & S

def main():
    inp = InputHelper()

    T = int(inp.read())
    for tc in range(T):
        n = int(inp.read())
        p = int(inp.read())

        bars = []
        for i in range(p):
            l = int(inp.read())
            bars.append(l)
        
        found = 0
        for i in range(1 << p): #iterate through all subsets
            sum = 0
            mask = i
            while mask > 0:
                ls = LSOne(mask)  #pick Least Sig Bit
                j = (ls ^ (ls-1)).bit_length()-1 #trailing zeroes
                sum += bars[j]
                mask -= ls
            if sum == n:
                found = 1
                break

        if found: 
            print("YES") 
        else: 
            print("NO")
        
if __name__ == '__main__':
    main()
