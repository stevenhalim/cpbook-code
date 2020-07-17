# This PR contains a Python 3 implementation of suffix array and some utility functions
# The suffix array construction was translated from https://cp-algorithms.com/string/suffix-array.html (not from CP4 version)
# AC on Kattis - dvaput and Kattis - stringmultimatching

def sort_cyclic_shifts(s):
    s = [*map(ord, s)]
    n = len(s)
    alphabet = 256
    p = [0] * n
    c = [0] * n
    cnt = [0] * max(alphabet, n)
    for i in range(n):
        cnt[s[i]] += 1
    for i in range(1, alphabet):
        cnt[i] += cnt[i-1]
    for i in range(n):
        cnt[s[i]] -= 1
        p[cnt[s[i]]] = i
    c[p[0]] = 0
    classes = 1
    for i in range(1, n):
        if s[p[i]] != s[p[i-1]]:
            classes += 1
        c[p[i]] = classes - 1
    pn = [0] * n
    cn = [0] * n
    h = 0
    while (1 << h) < n:
        for i in range(n):
            pn[i] = p[i] - (1 << h)
            if pn[i] < 0:
                pn[i] += n
        for i in range(classes):
            cnt[i] = 0
        for i in range(n):
            cnt[c[pn[i]]] += 1
        for i in range(1, classes):
            cnt[i] += cnt[i-1]
        for i in range(n-1, -1, -1):
            cnt[c[pn[i]]] -= 1
            p[cnt[c[pn[i]]]] = pn[i]
        cn[p[0]] = 0
        classes = 1
        for i in range(1, n):
            cur = (c[p[i]], c[(p[i] + (1 << h)) % n])
            prev = (c[p[i-1]], c[(p[i-1] + (1 << h)) % n])
            if cur != prev:
                classes += 1
            cn[p[i]] = classes - 1
        c, cn = cn, c
        h += 1
    return p

# returns the suffix array of s
def suffix_array_construction(s):
    return sort_cyclic_shifts(s+'\0')[1:]

# returns the lcp array of s given the suffix array
def lcp_construction(s, sa):
    n = len(s)
    rank = [0] * n
    for i in range(n):
        rank[sa[i]] = i
    k = 0
    lcp = [0] * (n-1)
    for i in range(n):
        if rank[i] == n-1:
            k = 0
            continue
        j = sa[rank[i]+1]
        while i + k < n and j + k < n and s[i+k] == s[j+k]:
            k += 1
        lcp[rank[i]] = k
        if k:
            k -= 1
    return [0] + lcp

# returns a pair (the LRS length and its index)
def longest_repeated_substring(lcp):
    idx = 0
    max_lcp = -1
    for i in range(1, len(lcp)):
        if lcp[i] > max_lcp:
            max_lcp = lcp[i]
            idx = i
    return (max_lcp, idx)

# returns a pair (the LCS length and its index)
def longest_common_substring(sa, lcp):
    idx = 0
    max_lcp = -1
    for i in range(1, n):
        if (sa[i] < m) != (sa[i-1] < m) and lcp[i] > lcs:
            max_lcp = lcp[i]
            idx = i
    return (max_lcp, idx)

# returns a pair of upper and lower bound, both inclusive
def string_matching(s, p, sa):
    m = len(p)
    lo = 0
    hi = len(s)-1
    while lo < hi:
        mid = (lo+hi)//2
        if s[sa[mid]:][:m] >= p:
            hi = mid
        else:
            lo = mid+1
    if s[sa[lo]:][:m] != p:
        return (-1, -1)
    l = lo
    lo = 0
    hi = len(s)-1
    while lo < hi:
        mid = (lo+hi)//2
        if s[sa[mid]:][:m] > p:
            hi = mid
        else:
            lo = mid+1
    if s[sa[hi]:][:m] != p:
        hi -= 1
    return (l, hi)

def main():
    s = "ACGACGGCTGCGGTAACCC#TTACGGCTGCGGTCCCCTT@CCCCCCGTTTACGGCTGCGGTGG$"
    n = len(s)
    sa = suffix_array_construction(s)
    print("\nThe Suffix Array of string s = '%s' is shown below (O(n log n) version):" % s)
    lcp = lcp_construction(s, sa)
    print("i\tsa[i]\tlcp[i]\tSuffix")
    for i in range(n):
        print("%2d\t%2d\t%2d\t%s" % (i, sa[i], lcp[i], s[sa[i]:]))

    i, j = longest_repeated_substring(lcp)
    print("\nThe LRS is '%s' with length = %d\n" % (s[sa[j]:][:i], i))

main()
