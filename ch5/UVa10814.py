# 0.040s in Python

from fractions import Fraction		# Python's built in fractions module

def main():
	N = int(input())
	for tc in range(N):
		frac = Fraction("".join(input().split(" ")))
		print(str(frac.numerator) + " / " + str(frac.denominator))

main()