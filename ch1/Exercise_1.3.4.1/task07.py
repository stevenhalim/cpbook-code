from string import ascii_uppercase
from itertools import permutations
print(*permutations(ascii_uppercase[:4]), sep='\n')
