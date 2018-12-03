import sys
allinputs = iter(sys.stdin.readlines())      # make Python I/O a bit faster
caseNo = 1
while True:
  [N, F] = map(int, next(allinputs).split())           # N bills, F friends
  if N == 0 and F == 0: break
  sum = 0                                      # native Big Integer support
  for _ in range(N):                                # sum the N large bills
    sum += int(next(allinputs))     # native Big Integer, will not overflow
  print("Bill #%d costs %d: each friend should pay %d\n"
    % (caseNo, sum, sum//F))    # integer divide the large sum to F friends
  caseNo += 1
