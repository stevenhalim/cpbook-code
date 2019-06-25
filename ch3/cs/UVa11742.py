import sys
import itertools

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


def main():
    inp = InputHelper()
    
    while 1:
        n = int(inp.read())
        m = int(inp.read())

        if n == 0 and m == 0:
            break

        constraints = []
        inp.readln()

        for i in range(m):
            a, b, c = map(int, inp.readln().split(" "))
            constraints.append((a, b, c))
        
        perm = list(itertools.permutations(range(n)))
        res = 0

        # try all possible O(n!) permutations, the largest nput 8! = 40320
        for arrangement in perm:
            all_ok = 1
       
            # check all constraints, max 20, each check 8 = 160 
            for constraint in constraints:
                i, j, k = constraint
                i_pos = -1
                j_pos = -1
                for ind in range(len(arrangement)):
                    if arrangement[ind] == i:
                        i_pos = ind
                    elif arrangement[ind] == j:
                        j_pos = ind

                d_pos = abs(i_pos - j_pos)
                if (k > 0): all_ok = d_pos <= k
                else: all_ok = d_pos >= abs(k)

                if all_ok == 0: break
            
            # all constraints are satisfied by this permutation
            if all_ok == 1:
                res += 1
        
        # the overall time complexity is thus O(m * n!)
        # overall complexity = 160 * 40320 = 6M, should be doable with pruning...
        print(res)
    
if __name__ == '__main__':
    main()
