from string import ascii_uppercase               # overkill, we can just use "ABCDEFGHIJ" below
from itertools import permutations
print(*permutations(ascii_uppercase[:4]), sep='\n') # change 4 to 10 to match the actual problem (but it will take some time to print)
