import java.util.*;

class HLD {
  private static ArrayList<ArrayList<Integer>> AL; // undirected tree
  private static ArrayList<Integer> par, heavy, group;

  private static int heavy_light(int x) {        // DFS traversal on tree
    int size = 1;
    int max_child_size = 0;
    for (Integer y : AL.get(x)) {                // edge x->y
      if (y == par.get(x)) continue;             // avoid cycle in a tree
      par.set(y, x);
      int child_size = heavy_light(y);           // recurse
      if (child_size > max_child_size) {
        max_child_size = child_size;
        heavy.set(x, y);                         // y is x's heaviest child
      }
      size += child_size;
    }
    return size;
  }

  private static void decompose(int x, int p) {
    group.set(x, p);                             // x is in group p
    for (Integer y : AL.get(x)) {                // edge x->y
      if (y == par.get(x)) continue;             // avoid cycle in a tree
      if (y == heavy.get(x))
        decompose(y, p);                         // y is in group p
      else
        decompose(y, y);                         // y is in a new group y
    }
  }

  public static void main(String[] args) {
    // as in Figure in HLD section, not yet rooted
    int N = 19;
    AL = new ArrayList<>();
    for (int i = 0; i < N; ++i)
      AL.add(new ArrayList<>());
    AL.get(0).add(1); AL.get(0).add(2); AL.get(0).add(3);
    AL.get(1).add(0); AL.get(1).add(4);
    AL.get(2).add(0); AL.get(2).add(5); AL.get(2).add(6); AL.get(2).add(7);
    AL.get(3).add(0); AL.get(3).add(8);
    AL.get(4).add(1); AL.get(4).add(9); AL.get(4).add(10);
    AL.get(5).add(2);
    AL.get(6).add(2);
    AL.get(7).add(2); AL.get(7).add(11); AL.get(7).add(12);
    AL.get(8).add(3);
    AL.get(9).add(4);
    AL.get(10).add(4); AL.get(10).add(13);
    AL.get(11).add(7); AL.get(11).add(14);
    AL.get(12).add(7); AL.get(12).add(15);
    AL.get(13).add(10);
    AL.get(14).add(11); AL.get(14).add(16);
    AL.get(15).add(12); AL.get(15).add(17); AL.get(15).add(18);
    AL.get(16).add(14);
    AL.get(17).add(15);
    AL.get(18).add(15);

    par = new ArrayList<>(Collections.nCopies(N, -1));
    heavy = new ArrayList<>(Collections.nCopies(N, -1));
    heavy_light(0); // start modified DFS from root 0
    group = new ArrayList<>(Collections.nCopies(N, -1));
    decompose(0, 0); // start labeling paths
    for (int i = 0; i < N; ++i)
      System.out.println(i + ", parent = " + par.get(i) + ", heaviest child = " + heavy.get(i) + ", belong to heavy-paths group = " + group.get(i));
  }
}
