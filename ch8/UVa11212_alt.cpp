#include <bits/stdc++.h>
using namespace std;

const int MAXD = 11;
const int MAXQ = 1e6 + 5; // maximum size of queue

int n, src, tgt, pk[MAXD], que[MAXQ];

void precomp() {
    pk[0] = 1;
    for (int i = 1; i < MAXD; ++i)
        pk[i] = pk[i - 1] * 10;
}

void init() {
    src = tgt = 0;
}

void readInput() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x; scanf("%d", &x);
        src = (src * 10) + x; // n is at most 9. Thus, it can be represented as a single integer.
        tgt = (tgt * 10) + i;
    }
}

// Fast shifter for the sequence of numbers.
int shiftVal(int v, int l, int r, int k) { 
    return (v / pk[n - l]) * pk[n - l] + // initial unmoved elements
           (v % pk[n - k]) + // initial unmoved elements 
           (v % pk[n - l]) / pk[n - r] * pk[n - k] + // move from  l ... r to begin at index k
           (v % pk[n - r]) / pk[n - k] * pk[n - k + (r - l)]; // move from r ... k to begin at index l
}

int solve() {
    if (src == tgt) return 0; // special case
    
    map<int, int> memo;
    memo[src] = 1; que[0] = src;
    memo[tgt] = 3; que[1] = tgt;
    // the distance and id are compressed as a single integer for speed up
    // initially a pair of integer {distance, id}
    // id represents whether it comes from src or tgt
    // it is set to 1 and 3 for speedup when checking whether a key exists in the map or not
    // binary representation :
    // - bit-0 : always 1, indicating that a key is present in the map
    // - bit-1 : 0 if it comes from src; 1 if it comes from tgt
    // - the other bits : represents the distance

    for (int ql = 0, qr = 2; ql < qr; ql++) { // it is faster to use fixed size of queue
        int cur = que[ql];
        int dst = memo[cur];
        for (int i = 0; i + 1 < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k <= n; k++) { // C(N, 3) loop for the edges
                    int nex = shiftVal(cur, i, j, k);
                    int nv = memo[nex];

                    if (nv) { // key is present
                        if ((nv & 2) == (dst & 2)) continue;
                        return (nv >> 2) + (dst >> 2) + 1;
                    } else { // if key is not present, the default return value is 0
                        memo[nex] = dst + 4;
                        que[qr++] = nex;
                    }
                }
    }
    assert(0); // it is guaranteed that the answer always exists
}

int main() {
    precomp();
    for (int cs = 1; ; cs++) {
        init();
        readInput();
        if (n == 0) break;

        printf("Case %d: %d\n", cs, solve());
    }
    return 0;
}