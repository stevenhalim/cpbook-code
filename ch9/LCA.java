import java.util.*;

class LCA {
  public static Vector< Vector < Integer > > children = new Vector < Vector < Integer > > ();
  public static int[] L = new int[2000], E = new int[2000], H = new int[2000];
  public static int idx;
  
  public static void dfs(int cur, int depth) {
    H[cur] = idx;
    E[idx] = cur;
    L[idx++] = depth;
    for (int i = 0; i < children.get(cur).size(); i++) {
      dfs(children.get(cur).get(i), depth+1);
      E[idx] = cur;                            // backtrack to current node
      L[idx++] = depth;
    }
  }

  public static void buildRMQ() {
    idx = 0;
    for (int i = 0; i < 2000; i++)
      H[i] = -1;
    dfs(0, 0);                     // we assume that the root is at index 0
  }

  public static void main(String[] args) {
    for (int i = 0; i < 10; i++)
      children.add(new Vector < Integer > ());

    children.get(0).add(1); children.get(0).add(7);
    children.get(1).add(2); children.get(1).add(3); children.get(1).add(6);
    children.get(3).add(4); children.get(3).add(5);
    children.get(7).add(8); children.get(7).add(9);

    buildRMQ();
    for (int i = 0; i < 2*10-1; i++) System.out.printf("%d ", H[i]);
    System.out.printf("\n");
    for (int i = 0; i < 2*10-1; i++) System.out.printf("%d ", E[i]);
    System.out.printf("\n");
    for (int i = 0; i < 2*10-1; i++) System.out.printf("%d ", L[i]);
    System.out.printf("\n");
  }
}
