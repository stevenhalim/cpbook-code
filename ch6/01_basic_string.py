import sys
import re
from collections import defaultdict

oneline = '';
first = True # technique to differentiate first line with the other lines
prev_dash = this_dash = False # to differentiate whether the previous line contains a dash or not
while True:
  thisline = input() # next(allinputs)
  if thisline == '.......': break
  if thisline.endswith('-'):
    thisline = thisline[:-1]
    this_dash = True
  else:
    this_dash = False
  if not first and not prev_dash:
    oneline += ' ' # only append ' ' if this line is the second one onwards
  first = False
  oneline += thisline
  prev_dash = this_dash

digits = alphas = vowels = consonants = 0
the_digit = list("0123456789")
the_alpha = list("abcdefghijklmnopqrstuvwxyz")
the_vowel = list("aeiou")
oneline = oneline.lower()
for c in oneline:
  digits += 1 if (c in the_digit) else 0
  alphas += 1 if (c in the_alpha) else 0
  vowels += 1 if (c in the_vowel) else 0
consonants = alphas-vowels;
print(oneline)
print(digits, vowels, consonants)

tokens = list(filter(None, re.split(' |\\.|,', oneline)))
freq = defaultdict(int)
for token in tokens: freq[token] += 1

tokens.sort()
print(tokens[0], tokens[-1])
hascs3233 = oneline.find('cs3233')
print(1 if hascs3233 else 0)

longline = input()
print(longline.count('s'), longline.count('h'), longline.count('7'))
