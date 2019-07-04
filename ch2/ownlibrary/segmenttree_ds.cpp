#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class SegmentTree {                              // OOP style
private:
  vi A;                                          // the underlying array
  int n;                                         // n = (int)A.size()
  vi st;                                         // segment tree array
  vi lazy;                                       // lazy propagation array

  int l(int p) { return  p<<1; }                 // go to left child
  int r(int p) { return (p<<1)+1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return A[a] <= A[b] ? a : b;                 // RMQ
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R)
      st[p] = L;                                 // base case
    else {
      int m = (L+R)/2;
      build(l(p), L  , m);
      build(r(p), m+1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != -1) {                         // has a lazy flag
      st[p] = L;                                 // [L..R] has same value
      if (L != R)                                // not a leaf
        lazy[l(p)] = lazy[r(p)] = lazy[p];       // propagate downwards
      else                                       // L == R, a single index
        A[L] = lazy[p];                          // time to update this
      lazy[p] = -1;                              // erase lazy flag
    }
  }

  void update(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      A[L] = val;
      lazy[p] = val;                             // update this
      propagate(p, L, R);                        // lazy propagation
    }
    else {
      int m = (L+R)/2;
      update(l(p), L  , m, i          , min(m, j), val);
      update(r(p), m+1, R, max(i, m+1), j        , val);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

  int RMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return -1;                        // infeasible
    if ((L >= i) && (R <= j)) return st[p];      // found the segment
    int m = (L+R)/2;
    return conquer(RMQ(l(p), L  , m, i          , min(m, j)),
                   RMQ(r(p), m+1, R, max(i, m+1), j        ));
  }

public:
  SegmentTree(int sz) : n(sz), st(4*n), lazy(4*n, -1) {}

  SegmentTree(const vi &_A) : SegmentTree((int)_A.size()) {
    A = _A;
    build(1, 0, n-1);
  }

  void update(int i, int j, int val) { update(1, 0, n-1, i, j, val); }

  int RMQ(int i, int j) { return RMQ(1, 0, n-1, i, j); }
};

int main() {
  vi A = {18, 17, 13, 19, 15, 11, 20, 99};       // make n a power of 2
  SegmentTree st(A);

  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("              A is {18,17,13,19,15,11,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // index 2
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // index 5
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // index 4

  st.update(5, 5, 77);                           // update A[5] to 77
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {18,17,13,19,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // remains index 2
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // now index 4
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // remains index 4

  st.update(0, 3, 30);                           // update A[0..3] to 30
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30,30,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // [0,1,2,3] all correct
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // remains index 4
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // remains index 4

  st.update(3, 3, 7);                            // update A[3] to 7
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30, 7,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));      // now index 3
  printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));      // remains index 4
  printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));      // now index 3

  return 0;    
}
