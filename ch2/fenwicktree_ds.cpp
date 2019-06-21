#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))

typedef vector<int> vi;

class FenwickTree {                              // index 0 is not used
private:
  vi ft;
public:
  FenwickTree(int n) {                           // create empty FT
    ft.assign(n+1, 0);
  }
  FenwickTree(const vi& f) {                     // create FT based on f
    int n = f.size()-1;                          // note f[0] is always 0
    ft.assign(n+1, 0);
    for (int i = 1; i <= n; ++i) {               // O(n)
      ft[i] += f[i];                             // add this value
      if (i+LSOne(i) <= n)                       // i has parent
        ft[i+LSOne(i)] += ft[i];                 // add to that parent
    }
  }
  int rsq(int j) {                               // returns RSQ(1, j)
    int sum = 0;
    for (; j; j -= LSOne(j))
      sum += ft[j];
    return sum;
  }
  int rsq(int i, int j) { return rsq(j) - rsq(i-1); } // returns RSQ(i, j)
  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, int v) {
    for (; i < ft.size(); i += LSOne(i))
      ft[i] += v;
  }
  int select(int k) {                            // O(log^2 n)
    int lo = 1, hi = ft.size()-1;
    for (int i = 0; i < 30; ++i) {               // 2^30 > 10^9; usually ok
      int mid = (lo+hi) / 2;                     // BSTA
      (rsq(1, mid) < k) ? lo = mid : hi = mid;
    }
    return hi;
  }
};

class RUPQ : FenwickTree {    // RUPQ variant is a simple extension of PURQ
public:
  RUPQ(int n) : FenwickTree(n) {}
  int point_query(int i) { return rsq(i); }
  void range_update(int i, int j, int v) { update(i, v), update(j+1, -v); }
};

int main() {
                           // idx   0 1 2 3 4 5 6 7  8 9 10, no index 0!
  FenwickTree ft1(10);     // ft = {-,0,0,0,0,0,0,0, 0,0,0}
  ft1.update(2, 1);        // ft = {-,0,1,0,1,0,0,0, 1,0,0}, idx 2,4,8 => +1
  ft1.update(4, 1);        // ft = {-,0,1,0,2,0,0,0, 2,0,0}, idx 4,8 => +1
  ft1.update(5, 2);        // ft = {-,0,1,0,2,2,2,0, 4,0,0}, idx 5,6,8 => +2
  ft1.update(6, 3);        // ft = {-,0,1,0,2,2,5,0, 7,0,0}, idx 6,8 => +3
  ft1.update(7, 2);        // ft = {-,0,1,0,2,2,5,2, 9,0,0}, idx 7,8 => +2
  ft1.update(8, 1);        // ft = {-,0,1,0,2,2,5,2,10,0,0}, idx 8 => +1
  ft1.update(9, 1);        // ft = {-,0,1,0,2,2,5,2,10,1,1}, idx 9,10 => +1
  printf("%d\n", ft1.rsq(1, 1));  // 0 => ft[1] = 0
  printf("%d\n", ft1.rsq(1, 2));  // 1 => ft[2] = 1
  printf("%d\n", ft1.rsq(1, 6));  // 7 => ft[6]+ft[4] = 5+2 = 7
  printf("%d\n", ft1.rsq(1, 10)); // 11 => ft[10]+ft[8] = 1+10 = 11
  printf("%d\n", ft1.rsq(3, 6));  // 6 => rsq(1, 6) - rsq(1, 2) = 7-1 = 6
  printf("%d\n", ft1.select(7));  // index 6, rsq(1, 6) == 7, which is >= 7
  printf("%d\n", ft1.select(8));  // index 7, rsq(1, 7) == 9, which is >= 8
  ft1.update(5, 2); // update demo
  printf("%d\n", ft1.rsq(1, 10)); // now 13

  printf("=====\n");

  vector<int> f = {0,0,1,0,1,2,3,2,1,1,0};  // index 0 is always 0 (unused)
  FenwickTree ft2(f);
  printf("%d\n", ft2.rsq(1, 1));  // 0 => ft[1] = 0
  printf("%d\n", ft2.rsq(1, 2));  // 1 => ft[2] = 1
  printf("%d\n", ft2.rsq(1, 6));  // 7 => ft[6]+ft[4] = 5+2 = 7
  printf("%d\n", ft2.rsq(1, 10)); // 11 => ft[10]+ft[8] = 1+10 = 11
  printf("%d\n", ft2.rsq(3, 6));  // 6 => rsq(1, 6) - rsq(1, 2) = 7-1 = 6
  printf("%d\n", ft2.select(7));  // index 6, rsq(1, 6) == 7, which is >= 7
  printf("%d\n", ft2.select(8));  // index 7, rsq(1, 7) == 9, which is >= 8
  ft2.update(5, 2); // update demo
  printf("%d\n", ft2.rsq(1, 10)); // now 13

  printf("=====\n");

  RUPQ rupq(10) ;                        // empty Fenwick Tree with 10 keys
  rupq.range_update(2, 9, 7);     // indices in [2, 3, .., 9] updated by +7
  rupq.range_update(6, 7, 3); // indices 6&7 are further updated by +3 (10)
  for (int i = 1; i <= 10; i++)
    printf("%d -> %d\n", i, rupq.point_query(i));

  return 0;
}
