import java.util.*;

class FenwickTree {
  private ArrayList<Integer> ft;

  private int LSOne(int S) { return (S & (-S)); }

  public FenwickTree() {}

  // initialization: n + 1 zeroes, ignore index 0
  public FenwickTree(int n) { 
    ft = new ArrayList<>();
    for (int i = 0; i <= n; i++) ft.add(0);
  }

  public int rsq(int j) {                              // returns RSQ(1, j)
    int sum = 0; for (; j > 0; j -= LSOne(j)) sum += ft.get(j);
    return sum; }

  public int rsq(int i, int j) {                       // returns RSQ(i, j)
    return rsq(j) - rsq(i-1); }

  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, int v) {                      // note: n = ft.size()-1
    for (; i < (int)ft.size(); i += LSOne(i)) ft.set(i, ft.get(i)+v); }
};

class fenwicktree_ds {
  public static void main(String[] args) {
                                          // idx   0 1 2 3 4 5 6 7  8 9 10, no index 0!
    FenwickTree ft = new FenwickTree(10); // ft = {-,0,0,0,0,0,0,0, 0,0,0}
    ft.update(2, 1);                      // ft = {-,0,1,0,1,0,0,0, 1,0,0}, idx 2,4,8 => +1
    ft.update(4, 1);                      // ft = {-,0,1,0,2,0,0,0, 2,0,0}, idx 4,8 => +1
    ft.update(5, 2);                      // ft = {-,0,1,0,2,2,2,0, 4,0,0}, idx 5,6,8 => +2
    ft.update(6, 3);                      // ft = {-,0,1,0,2,2,5,0, 7,0,0}, idx 6,8 => +3
    ft.update(7, 2);                      // ft = {-,0,1,0,2,2,5,2, 9,0,0}, idx 7,8 => +2
    ft.update(8, 1);                      // ft = {-,0,1,0,2,2,5,2,10,0,0}, idx 8 => +1
    ft.update(9, 1);                      // ft = {-,0,1,0,2,2,5,2,10,1,1}, idx 9,10 => +1
    System.out.printf("%d\n", ft.rsq(1, 1));  // 0 => ft[1] = 0
    System.out.printf("%d\n", ft.rsq(1, 2));  // 1 => ft[2] = 1
    System.out.printf("%d\n", ft.rsq(1, 6));  // 7 => ft[6] + ft[4] = 5 + 2 = 7
    System.out.printf("%d\n", ft.rsq(1, 10)); // 11 => ft[10] + ft[8] = 1 + 10 = 11
    System.out.printf("%d\n", ft.rsq(3, 6));  // 6 => rsq(1, 6) - rsq(1, 2) = 7 - 1

    ft.update(5, 2); // update demo
    System.out.printf("%d\n", ft.rsq(1, 10)); // now 13
  }
}
