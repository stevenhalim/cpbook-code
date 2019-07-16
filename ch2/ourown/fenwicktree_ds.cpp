#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))                    // the key operation

typedef long long ll;                            // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

class FenwickTree {                              // index 0 is not used
private:
  vll ft;                                        // internal FT is an array
public:
  FenwickTree(int n) { ft.assign(n+1, 0); }      // create an empty FT

  void build(const vll &f) {
    int n = (int)f.size()-1;                     // note f[0] is always 0
    ft.assign(n+1, 0);
    for (int i = 1; i <= n; ++i) {               // O(n)
      ft[i] += f[i];                             // add this value
      if (i+LSOne(i) <= n)                       // i has parent
        ft[i+LSOne(i)] += ft[i];                 // add to that parent
    }
  }

  FenwickTree(const vll &f) { build(f); }        // create FT based on f

  FenwickTree(int n, const vi &s) {              // create FT based on s
    vll f(n+1, 0);
    for (int i = 0; i < (int)s.size(); ++i)      // do the conversion first
      ++f[s[i]];
    build(f);
  }

  ll rsq(int j) {                                // returns RSQ(1, j)
    ll sum = 0;
    for (; j; j -= LSOne(j))
      sum += ft[j];
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // inc/exclusion

  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, ll v) {
    for (; i < (int)ft.size(); i += LSOne(i))
      ft[i] += v;
  }

  int select(ll k) {                             // O(log^2 n)
    int lo = 1, hi = ft.size()-1;
    for (int i = 0; i < 30; ++i) {               // 2^30 > 10^9; usually ok
      int mid = (lo+hi) / 2;                     // BSTA
      (rsq(1, mid) < k) ? lo = mid : hi = mid;   // See Section 3.3.1
    }
    return hi;
  }
};

class RUPQ {                                     // RUPQ variant
private:
  FenwickTree ft;                                // internally use PURQ FT
public:
  RUPQ(int n) : ft(FenwickTree(n)) {}
  void range_update(int ui, int uj, int v) {
    ft.update(ui, v);                            // [ui, ui+1, .., n] +v
    ft.update(uj+1, -v);                         // [uj+1, uj+2, .., n] -v
  }                                              // [ui, ui+1, .., uj] +v
  ll point_query(int i) { return ft.rsq(i); }    // rsq(i) is sufficient
};

class RURQ  {                                    // RURQ variant
private:                                         // needs two helper FTs
  RUPQ rupq;                                     // one RUPQ and
  FenwickTree purq;                              // one PURQ
public:
  RURQ(int n) : rupq(RUPQ(n)), purq(FenwickTree(n)) {} // initialization
  void range_update(int ui, int uj, int v) {
    rupq.range_update(ui, uj, v);                // [ui, ui+1, .., uj] +v
    purq.update(ui, v*(ui-1));                   // -(ui-1)*v before ui
    purq.update(uj+1, -v*uj);                    // +(uj-ui+1)*v after uj
  }
  ll rsq(int j) {
    return rupq.point_query(j)*j -               // optimistic calculation
           purq.rsq(j);                          // cancelation factor
  }
  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // standard
};

int main() {
  vll f = {0,0,1,0,1,2,3,2,1,1,0};               // index 0 is always 0
  FenwickTree ft(f);
  printf("%lld\n", ft.rsq(1, 6)); // 7 => ft[6]+ft[4] = 5+2 = 7
  printf("%d\n", ft.select(7)); // index 6, rsq(1, 6) == 7, which is >= 7
  ft.update(5, 1); // update demo
  printf("%lld\n", ft.rsq(1, 10)); // now 12
  printf("=====\n");
  RUPQ rupq(10); RURQ rurq(10);
  rupq.range_update(2, 9, 7); // indices in [2, 3, .., 9] updated by +7
  rurq.range_update(2, 9, 7);
  rupq.range_update(6, 7, 3); // indices 6&7 are further updated by +3 (10)
  rurq.range_update(6, 7, 3);
  for (int i = 1; i <= 10; i++)
    printf("%d -> %lld\n", i, rupq.point_query(i));
  printf("RSQ(1, 10) = %lld\n", rurq.rsq(1, 10)); // 62
  printf("RSQ(6, 7) = %lld\n", rurq.rsq(6, 7)); // 20
  return 0;
}

/*
int main() {
  printf("Manual Fenwick Tree construction\n");
                           // idx   0 1 2 3 4 5 6 7  8 9 10, no index 0!
  FenwickTree ft1(10);     // ft = {-,0,0,0,0,0,0,0, 0,0,0}
  ft1.update(2, 1);        // ft = {-,0,1,0,1,0,0,0, 1,0,0}, idx 2,4,8 => +1
  ft1.update(4, 1);        // ft = {-,0,1,0,2,0,0,0, 2,0,0}, idx 4,8 => +1
  ft1.update(5, 2);        // ft = {-,0,1,0,2,2,2,0, 4,0,0}, idx 5,6,8 => +2
  ft1.update(6, 3);        // ft = {-,0,1,0,2,2,5,0, 7,0,0}, idx 6,8 => +3
  ft1.update(7, 2);        // ft = {-,0,1,0,2,2,5,2, 9,0,0}, idx 7,8 => +2
  ft1.update(8, 1);        // ft = {-,0,1,0,2,2,5,2,10,0,0}, idx 8 => +1
  ft1.update(9, 1);        // ft = {-,0,1,0,2,2,5,2,10,1,1}, idx 9,10 => +1
  printf("%lld\n", ft1.rsq(1, 1));  // 0 => ft[1] = 0
  printf("%lld\n", ft1.rsq(1, 2));  // 1 => ft[2] = 1
  printf("%lld\n", ft1.rsq(1, 6));  // 7 => ft[6]+ft[4] = 5+2 = 7
  printf("%lld\n", ft1.rsq(1, 10)); // 11 => ft[10]+ft[8] = 1+10 = 11
  printf("%lld\n", ft1.rsq(3, 6));  // 6 => rsq(1, 6) - rsq(1, 2) = 7-1 = 6
  printf("%d\n", ft1.select(7));  // index 6, rsq(1, 6) == 7, which is >= 7
  printf("%d\n", ft1.select(8));  // index 7, rsq(1, 7) == 9, which is >= 8
  ft1.update(5, 2); // update demo
  printf("%lld\n", ft1.rsq(1, 10)); // now 13

  printf("=====\n");

  printf("Fenwick Tree construction using raw data\n");
  vi s = {2,4,5,6,5,6,8,6,7,9,7};
  FenwickTree ft2(10, s); // identical as ft1
  printf("%lld\n", ft2.rsq(1, 1));  // 0 => ft[1] = 0
  printf("%lld\n", ft2.rsq(1, 2));  // 1 => ft[2] = 1
  printf("%lld\n", ft2.rsq(1, 6));  // 7 => ft[6]+ft[4] = 5+2 = 7
  printf("%lld\n", ft2.rsq(1, 10)); // 11 => ft[10]+ft[8] = 1+10 = 11
  printf("%lld\n", ft2.rsq(3, 6));  // 6 => rsq(1, 6) - rsq(1, 2) = 7-1 = 6
  printf("%d\n", ft2.select(7));  // index 6, rsq(1, 6) == 7, which is >= 7
  printf("%d\n", ft2.select(8));  // index 7, rsq(1, 7) == 9, which is >= 8
  ft2.update(5, 2); // update demo
  printf("%lld\n", ft2.rsq(1, 10)); // now 13

  printf("=====\n");

  printf("Fenwick Tree construction using frequency data\n");
  vll f = {0,0,1,0,1,2,3,2,1,1,0};  // index 0 is always 0 (unused)
  FenwickTree ft3(f);
  printf("%lld\n", ft3.rsq(1, 1));  // 0 => ft[1] = 0
  printf("%lld\n", ft3.rsq(1, 2));  // 1 => ft[2] = 1
  printf("%lld\n", ft3.rsq(1, 6));  // 7 => ft[6]+ft[4] = 5+2 = 7
  printf("%lld\n", ft3.rsq(1, 10)); // 11 => ft[10]+ft[8] = 1+10 = 11
  printf("%lld\n", ft3.rsq(3, 6));  // 6 => rsq(1, 6) - rsq(1, 2) = 7-1 = 6
  printf("%d\n", ft3.select(7));  // index 6, rsq(1, 6) == 7, which is >= 7
  printf("%d\n", ft3.select(8));  // index 7, rsq(1, 7) == 9, which is >= 8
  ft3.update(5, 2); // update demo
  printf("%lld\n", ft3.rsq(1, 10)); // now 13
  printf("=====\n");
  RUPQ rupq(10); RURQ rurq(10);
  rupq.range_update(2, 9, 7); // indices in [2, 3, .., 9] updated by +7
  rurq.range_update(2, 9, 7);
  rupq.range_update(6, 7, 3); // indices 6&7 are further updated by +3 (10)
  rurq.range_update(6, 7, 3);
  for (int i = 1; i <= 10; i++)
    printf("%d -> %lld\n", i, rupq.point_query(i));
  printf("RSQ(1, 10) = %lld\n", rurq.rsq(1, 10)); // 62
  printf("RSQ(6, 7) = %lld\n", rurq.rsq(6, 7)); // 20


  // RUPQ rupq(10) ;                        // empty Fenwick Tree with 10 keys
  // rupq.range_update(2, 9, 7);     // indices in [2, 3, .., 9] updated by +7
  // rupq.range_update(6, 7, 3); // indices 6&7 are further updated by +3 (10)
  // for (int i = 1; i <= 10; i++)
  //   printf("%d -> %lld\n", i, rupq.point_query(i));

  // printf("=====\n");

  // RURQ rurq(10);
  // rurq.range_update(2, 2, 1);
  // rurq.range_update(4, 9, 1);
  // rurq.range_update(5, 7, 1);
  // rurq.range_update(6, 6, 1);
  // for (int i = 1; i <= 10; i++)
  //   printf("%d -> %lld\n", i, rurq.rsq(i));
  // printf("RSQ(6, 10) = %lld\n", rurq.rsq(6, 10)); // 3+2+1+1+0 = 7
  // printf("RSQ(1, 10) = %lld\n", rurq.rsq(1, 10)); // m = 11

  return 0;
}
*/
