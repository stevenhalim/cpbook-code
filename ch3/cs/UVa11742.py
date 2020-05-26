import sys
import itertools

def main():
    while True:
        n, m = map(int, input().split())
        if n == 0 and m == 0:
            break

        constraints = []
        for i in range(m):
            a, b, c = map(int, input().split())
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
    
main()
