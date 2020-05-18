import math

def isOn(S, j):
    return (S & (1<<j))

def setBit(S, j):
    return (S | (1<<j))

def clearBit(S, j):
    return (S & (~(1<<j)))

def toggleBit(S, j):
    return (S ^ (1<<j))

def lowBit(S):
    return (S&(-S))

def setAll(n):
    return ((1<<n)-1)

def modulo(S, N): # returns S % N, where N is a power of 2
    return ((S) & (N-1))

def isPowerOfTwo(S):
    return (not(S & (S - 1)))

def nearestPowerOfTwo(S):
    return 1<<round(math.log2(S))

def turnOffLastBit(S):
    return (S & (S - 1))

def turnOnLastZero(S):
    return ((S) | (S + 1))

def turnOffLastConsecutiveBits(S):
    return ((S) & (S + 1))

def turnOnLastConsecutiveZeroes(S):
    return ((S) | (S-1))


def printSet(vS):           # in binary representation
    print("S = {} = {:b}".format(vS, vS))

def main():
    
    print("1. Representation (all indexing are 0-based and counted from right)")
    S = 34
    printSet(S)
    print()

    print("2. Multiply S by 2, then divide S by 4 (2x2), then by 2")
    S = 34
    printSet(S)
    S = S << 1
    printSet(S)
    S = S >> 2
    printSet(S)
    S = S >> 1
    printSet(S)
    print()


    print("3. Set/turn on the 3-rd item of the set")
    S = 34
    printSet(S)
    S = setBit(S, 3)
    printSet(S)
    print()

    print("4. Check if the 3-rd and then 2-nd item of the set is on?")
    S = 42
    printSet(S)
    T = isOn(S, 3)
    print("T = {}, {}".format(T, "ON" if T else "OFF"))
    T = isOn(S, 2)
    print("T = {}, {}".format(T, "ON" if T else "OFF"))
    print()

    print("5. Clear/turn off the 1-st item of the set")
    S = 42
    printSet(S)
    S = clearBit(S, 1)
    printSet(S)
    print()

    print("6. Toggle the 2-nd item and then 3-rd item of the set")
    S = 40
    printSet(S)
    S = toggleBit(S, 2)
    printSet(S)
    S = toggleBit(S, 3)
    printSet(S)
    print()

    print("7. Check the first bit from right that is on")
    S = 40
    printSet(S)
    T = lowBit(S)
    print("T = {} (this is always a power of 2)".format(T))
    S = 52
    printSet(S)
    T = lowBit(S)
    print("T = {} (this is always a power of 2)".format(T))
    print();

    print("8. Turn on all bits in a set of size n = 6")
    S = setAll(6)
    printSet(S)
    print()

    print("9. Other tricks (not shown in the book)")
    print("8 % 4 = {}".format(modulo(8, 4)))
    print("7 % 4 = {}".format(modulo(7, 4)))
    print("6 % 4 = {}".format(modulo(6, 4)))
    print("5 % 4 = {}".format(modulo(5, 4)))
    print("is {} power of two? {}".format(9, isPowerOfTwo(9)))
    print("is {} power of two? {}".format(8, isPowerOfTwo(8)))
    print("is {} power of two? {}".format(7, isPowerOfTwo(7)))
    for i in range(1, 17):
        print("Nearest power of two of {} is {}".format(i, nearestPowerOfTwo(i)))
    print("S = {}, turn off last bit in S, S = {}".format(40, turnOffLastBit(40)))
    print("S = {}, turn on last zero in S, S = {}".format(41, turnOnLastZero(41)))
    print("S = {}, turn off last consecutive bits in S, S = {}".format(39, turnOffLastConsecutiveBits(39)))
    print("S = {}, turn on last consecutive zeroes in S, S = {}".format(36, turnOnLastConsecutiveZeroes(36)))

main()
