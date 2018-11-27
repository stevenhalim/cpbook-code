#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))

typedef vector<int> vi;

class FenwickTree {                    // remember that index 0 is not used
private: vi ft; int n;        // recall that vi is: typedef vector<int> vi;
public: FenwickTree(int _n) : n(_n) { ft.assign(n+1, 0); }    // n+1 zeroes
  FenwickTree(const vi& f) : n(f.size()-1) { ft.assign(n+1, 0);
    for (int i = 1; i <= n; i++) {                                  // O(n)
      ft[i] += f[i];                                      // add this value
      if (i+LSOne(i) <= n)    // if index i has parent in the updating tree
        ft[i+LSOne(i)] += ft[i]; } }       // add this value to that parent
  int rsq(int j) {                                     // returns RSQ(1, j)
    int sum = 0; for (; j; j -= LSOne(j)) sum += ft[j];
    return sum; }
  int rsq(int i, int j) { return rsq(j) - rsq(i-1); }  // returns RSQ(i, j)
  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, int v) {
    for (; i <= n; i += LSOne(i)) ft[i] += v; }    // note: n = ft.size()-1
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
  ft2.update(5, 2); // update demo
  printf("%d\n", ft2.rsq(1, 10)); // now 13
} // return 0;
