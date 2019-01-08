import java.util.*;

// Union-Find Disjoint Sets Library written in OOP manner, using both path compression and union by rank heuristics
class UnionFind {                                              // OOP style
  private ArrayList<Integer> p, rank, setSize;
  private int numSets;

  public UnionFind(int N) {
    p = new ArrayList<>(N);
    rank = new ArrayList<>(N);
    setSize = new ArrayList<>(N);
    numSets = N;
    for (int i = 0; i < N; i++) {
      p.add(i);
      rank.add(0);
      setSize.add(1);
    }
  }

  public int findSet(int i) { 
    if (p.get(i) == i) return i;
    else {
      int ret = findSet(p.get(i)); p.set(i, ret);
      return ret; } }

  public Boolean isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  public void unionSet(int i, int j) { 
    if (!isSameSet(i, j)) { numSets--; 
    int x = findSet(i), y = findSet(j);
    // rank is used to keep the tree short
    if (rank.get(x) > rank.get(y)) { p.set(y, x); setSize.set(x, setSize.get(x) + setSize.get(y)); }
    else                           { p.set(x, y); setSize.set(y, setSize.get(y) + setSize.get(x));
                                     if (rank.get(x) == rank.get(y)) rank.set(y, rank.get(y) + 1); } } }
  public int numDisjointSets() { return numSets; }
  public int sizeOfSet(int i) { return setSize.get(findSet(i)); }
}

class unionfind_ds {
  public static void main(String[] args) {
    System.out.printf("Assume that there are 5 disjoint sets initially\n");
    UnionFind UF = new UnionFind(5); // create 5 disjoint sets
    System.out.printf("%d\n", UF.numDisjointSets()); // 5
    UF.unionSet(0, 1);
    System.out.printf("%d\n", UF.numDisjointSets()); // 4
    UF.unionSet(2, 3);
    System.out.printf("%d\n", UF.numDisjointSets()); // 3
    UF.unionSet(4, 3);
    System.out.printf("%d\n", UF.numDisjointSets()); // 2
    System.out.printf("isSameSet(0, 3) = %b\n", UF.isSameSet(0, 3)); // will return false
    System.out.printf("isSameSet(4, 3) = %b\n", UF.isSameSet(4, 3)); // will return true
    for (int i = 0; i < 5; i++) // findSet will return 1 for {0, 1} and 3 for {2, 3, 4}
      System.out.printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n", i, UF.findSet(i), i, UF.sizeOfSet(i));
    UF.unionSet(0, 3);
    System.out.printf("%d\n", UF.numDisjointSets()); // 1
    for (int i = 0; i < 5; i++) // findSet will return 3 for {0, 1, 2, 3, 4}
      System.out.printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n", i, UF.findSet(i), i, UF.sizeOfSet(i));
  }
}
