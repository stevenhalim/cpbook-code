#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class SegmentTree { // the OOP Segment Tree implementation, like Heap array
private: vi st, A;            // recall that vi is: typedef vector<int> vi;
  int n;
  int left (int p) { return  p<<1; }      // same as binary heap operations
  int right(int p) { return (p<<1) + 1; }

  void build(int p, int L, int R) {                           // O(n log n)
    if (L == R)                            // as L == R, either one is fine
      st[p] = L;                                         // store the index
    else {                                // recursively compute the values
      build(left(p) , L          , (L+R)/2);
      build(right(p), (L+R)/2 + 1, R      );
      int p1 = st[left(p)], p2 = st[right(p)];
      st[p] = (A[p1] <= A[p2]) ? p1 : p2;
  } }

  int rmq(int p, int L, int R, int i, int j) {                  // O(log n)
    if (i >  R || j <  L) return -1; // current segment outside query range
    if (L >= i && R <= j) return st[p];               // inside query range
     // compute the min position in the left and right part of the interval
    int p1 = rmq(left(p) , L        , (L+R)/2, i, j);
    int p2 = rmq(right(p), (L+R)/2+1, R      , i, j);
    if (p1 == -1) return p2;   // if we try to access segment outside query
    if (p2 == -1) return p1;                               // same as above
    return (A[p1] <= A[p2]) ? p1 : p2; }          // as as in build routine

  int update(int p, int L, int R, int idx, int new_value) {
    int i = idx, j = idx;                   // for point update i = j = idx
         // if the current interval does not intersect the update interval, 
    if (i > R || j < L) return st[p];         // return this st node value!
    // if the current interval is included in the update range,
    if (L == i && R == j) {
      A[i] = new_value;                      // update the underlying array
      return st[p] = L;                                       // this index
    }
     // compute the minimum position in the left/right part of the interval
    int p1, p2;
    p1 = update(left(p) , L        , (L+R)/2, idx, new_value);
    p2 = update(right(p), (L+R)/2+1, R      , idx, new_value);
    // return the position where the overall minimum is
    return st[p] = (A[p1] <= A[p2]) ? p1 : p2;
  }

public:
  SegmentTree(const vi &_A) {
    A = _A; n = (int)A.size();              // copy content for local usage
    st.assign(4*n, 0);              // create large enough vector of zeroes
    build(1, 0, n-1);                                    // recursive build
  }
  int rmq(int i, int j) { return rmq(1, 0, n-1, i, j); }     // overloading
  int update(int i, int v) {                                // point update
    return update(1, 0, n-1, i, v); }
};
  
int main() {
  int arr[] = {18, 17, 13, 19, 15, 11, 20};           // the original array
  vi A(arr, arr+7);                        // copy the contents to a vector
  SegmentTree st(A);

  printf("              idx    0, 1, 2, 3, 4, 5, 6\n");
  printf("              A is {18,17,13,19,15,11,20}\n");
  printf("RMQ(1, 3) = %d\n", st.rmq(1, 3));             // answer = index 2
  printf("RMQ(4, 6) = %d\n", st.rmq(4, 6));             // answer = index 5
  printf("RMQ(3, 4) = %d\n", st.rmq(3, 4));             // answer = index 4
  printf("RMQ(0, 0) = %d\n", st.rmq(0, 0));             // answer = index 0
  printf("RMQ(0, 1) = %d\n", st.rmq(0, 1));             // answer = index 1
  printf("RMQ(0, 6) = %d\n", st.rmq(0, 6));             // answer = index 5

  printf("              idx    0, 1, 2, 3, 4, 5, 6\n");
  printf("Now, modify A into {18,17,13,19,15,99,20}\n");
  st.update(5, 99);                            // update A[5] from 11 to 99
  printf("These values do not change\n");
  printf("RMQ(1, 3) = %d\n", st.rmq(1, 3));                            // 2
  printf("RMQ(3, 4) = %d\n", st.rmq(3, 4));                            // 4
  printf("RMQ(0, 0) = %d\n", st.rmq(0, 0));                            // 0
  printf("RMQ(0, 1) = %d\n", st.rmq(0, 1));                            // 1
  printf("These values change\n");
  printf("RMQ(0, 6) = %d\n", st.rmq(0, 6));  // answer changes = index 5->2
  printf("RMQ(4, 6) = %d\n", st.rmq(4, 6));  // answer changes = index 5->4
  printf("RMQ(4, 5) = %d\n", st.rmq(4, 5));  // answer changes = index 5->4

  return 0;
}
