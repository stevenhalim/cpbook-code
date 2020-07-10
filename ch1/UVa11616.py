import sys

def AtoR(A):
    m = {1000: 'M', 900: 'CM', 500: 'D', 400: 'CD', 100: 'C', 90: 'XC',\
         50: 'L', 40: 'XL', 10: 'X', 9: 'IX', 5: 'V', 4: 'IV', 1: 'I'}
    A = int(A)
    for value, roman in m.items():
        while A >= value:
            print(roman, end='')
            A -= value
    print()

def RtoA(R):
    m = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
    value = 0
    for i in range(len(R)):
        if i+1 < len(R) and m[R[i]] < m[R[i+1]]:
            value += m[R[i+1]] - m[R[i]]
        elif i-1 >= 0 and m[R[i-1]] < m[R[i]]:
            continue
        else:
            value += m[R[i]]
    print(value)

def main():
    for s in sys.stdin:
        s = s.strip('\n')
        if s.isdigit():
            AtoR(s)
        else:
            RtoA(s)

main()
