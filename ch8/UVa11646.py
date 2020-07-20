# Athletics Track
# see the figure in Chapter 8.7
# the key = center of circle is at center of track

import sys,math

caseNo = 0
for a_colon_b in sys.stdin:
    a,colon,b = a_colon_b.split()
    a = int(a)
    b = int(b)
    lo = 0.0
    hi = 400.0                                   # the range of answer
    for _ in range(40):
        L = (lo+hi) / 2.0                        # bisection method on L
        W = b/a*L                                # derive W from L and a:b
        expected_arc = (400 - 2.0*L) / 2.0       # reference value
        CM = 0.5*L
        MX = 0.5*W                               # Apply Trigonometry here
        r = math.sqrt(CM*CM + MX*MX)
        angle = 2.0 * math.atan(MX/CM) * 180.0/math.pi
        this_arc = angle/360.0 * math.pi * (2.0*r)
        if this_arc > expected_arc:
            hi = L
        else:
            lo = L
    caseNo += 1
    print("Case {:d}: {:.12f} {:.12f}".format(caseNo, L, W))
