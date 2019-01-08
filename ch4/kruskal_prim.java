import java.util.*;
import java.io.*;

// Union-Find Disjoint Sets Library written in OOP manner, using both path compression and union by rank heuristics
class UnionFind {                                              // OOP style
  private ArrayList<Integer> p, rank, setSize;
  private int numSets;

  public UnionFind(int N) {
    p = new ArrayList<Integer>(N);
    rank = new ArrayList<Integer>(N);
    setSize = new ArrayList<Integer>(N);
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

public class kruskal_prim {
  static ArrayList<ArrayList<IntegerPair>> AL = new ArrayList<>();
  static ArrayList<Boolean> taken = new ArrayList<>(); // global boolean flag to avoid cycle
  static PriorityQueue<IntegerPair> pq = new PriorityQueue<>(); // priority queue to help choose shorter edges

  static void process(int u) { //  we do not need to use -ve sign to reverse the sort order
    taken.set(u, true);
    for (IntegerPair v_w : AL.get(u))
      if (!taken.get(v_w.first()))
        pq.offer(new IntegerPair(v_w.second(), v_w.first()));
  }

  public static void main(String[] args) throws Exception {
    /*
    // Graph in Figure 4.10 left, format: list of weighted edges
    // This example shows another form of reading graph input
    5 7
    0 1 4
    0 2 4
    0 3 6
    0 4 6
    1 2 2
    2 3 8
    3 4 9
    */

    File f = new File("kruskal_prim_in.txt");
    Scanner sc = new Scanner(f);

    int V = sc.nextInt();
    int E = sc.nextInt();
    // Kruskal's algorithm merged with Prim's algorithm

    AL.clear();
    for (int i = 0; i < V; i++) {
      ArrayList<IntegerPair> Neighbor = new ArrayList<>(); // create ArrayList of pair<int, int> 
      AL.add(Neighbor); // store blank ArrayList first
    }
    ArrayList<IntegerTriple> EL = new ArrayList<>();
  
    // sort by edge weight O(E log E)
    // PQ default: sort descending. Trick: use <(negative) weight(i, j), <i, j> >
    for (int i = 0; i < E; i++) {
      int u = sc.nextInt();
      int v = sc.nextInt();
      int w = sc.nextInt();
      EL.add(new IntegerTriple(w, u, v));                      // (w, u, v)
      AL.get(u).add(new IntegerPair(v, w));
      AL.get(v).add(new IntegerPair(u, w));
    }
    Collections.sort(EL);

    int mst_cost = 0;           // all V are disjoint sets at the beginning
    UnionFind UF = new UnionFind(V);
    for (int i = 0; i < E; i++) {                    // for each edge, O(E)
      IntegerTriple front = EL.get(i);
      if (!UF.isSameSet(front.second(), front.third())) {          // check
        mst_cost += front.first();            // add the weight of e to MST
        UF.unionSet(front.second(), front.third());            // link them
    } }

    // note: the number of disjoint sets must eventually be 1 for a valid MST
    System.out.printf("MST cost = %d (Kruskal's)\n", mst_cost);



  // inside int main() --- assume the graph is stored in AL, pq is empty
    for (int i = 0; i < V; i++)
      taken.add(false);                // no vertex is taken at the beginning
    process(0);   // take vertex 0 and process all edges incident to vertex 0
    mst_cost = 0;
    while (!pq.isEmpty()) { // repeat until V vertices (E=V-1 edges) are taken
      IntegerPair front = pq.peek(); pq.poll();
      int u = front.second(), w = front.first();   // no need to negate id/weight
      if (!taken.get(u)) {           // we have not connected this vertex yet
        mst_cost += w;
        process(u); // take u, process all edges incident to u
      }
    }                                        // each edge is in pq only once!
    System.out.printf("MST cost = %d (Prim's)\n", mst_cost);
  }
}
