import sys
inputs = sys.stdin.read().splitlines()           # make Python I/O faster
caseNo = 1
ln = 0
while True:
    N, F = map(int, inputs[ln].split())          # N bills, F friends
    ln += 1
    if N == 0 and F == 0: break
    sum = 0                                      # native support
    for _ in range(N):                           # sum the N large bills
        sum += int(inputs[ln])                   # native Big Integer
        ln += 1
    print("Bill #%d costs %d: each friend should pay %d\n"
        % (caseNo, sum, sum//F))                 # integer division
    caseNo += 1
