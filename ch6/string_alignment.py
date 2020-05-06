def main():
    A = "ACAATCC"
    B = "AGCATGC"
    n = len(A)
    m = len(B)

    table = [[0 for j in range(20)] for i in range(20)] # Needleman Wunsnch's algorithm

    for i in range(1, n+1):
        table[i][0] = i * -1
    for j in range(1, m+1):
        table[0][j] = j * -1

    for i in range(1, n+1):
        for j in range(1, m+1):
            # match = 2 points, mismatch = -1 point
            table[i][j] = table[i - 1][j - 1] + (2 if A[i - 1] == B[j - 1] else -1)
            # insert/delete = -1 point
            table[i][j] = max(table[i][j], table[i - 1][j] - 1); # delete
            table[i][j] = max(table[i][j], table[i][j - 1] - 1); # insert

    print("DP table:")
    for i in range(0, n+1):
        for j in range(0, m+1):
            print("{:>3}".format(table[i][j]), end='')
        print()

    print("Maximum Alignment Score: {}".format(table[n][m]))

main()
