import re
from collections import Counter

def first_block():
    while True:
        line = input()
        if line == '.......':
            break
        yield line

oneline = ' '.join(first_block()).replace('- ', '').lower()

digits, alphas, vowels = (sum(pred(c) for c in oneline)
                            for pred
                            in (lambda c: c.isdigit(),
                                lambda c: c.isalpha(),
                                lambda c: c in 'aeiou'))
consonants = alphas - vowels

print(oneline)
print(digits, vowels, consonants)

tokens = list(filter(None, re.split(' |\\.|,', oneline)))
freq = Counter(tokens)

print(min(tokens), max(tokens))
print(1 if 'cs3233' in oneline else 0)

longline = input()
print(longline.count('s'), longline.count('h'), longline.count('7'))
