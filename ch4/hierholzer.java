import java.util.*;
import java.text.*;

class hierholzer {
  private static int N;
  private static ArrayList<ArrayList<Integer>> AL; // Directed graph

  private static ArrayList<Integer> hierholzer(int s) {
    ArrayList<Integer> ans = new ArrayList<>();
    ArrayList<Integer> idx = new ArrayList<>(Collections.nCopies(N, 0));
    ArrayList<Integer> st = new ArrayList<>();
    st.add(s);
    while (!st.isEmpty()) {
      int u = st.get(st.size()-1);
      if (idx.get(u) < AL.get(u).size()) {       // still has neighbor
        st.add(AL.get(u).get(idx.get(u)));
        idx.set(u, idx.get(u)+1);
      }
      else {
        ans.add(u);
        st.remove(st.size()-1);
      }
    }
    Collections.reverse(ans);
    return ans;
  }

  public static void main(String[] args) {
    // The directed graph shown in Figure 4.40
    N = 7;
    AL = new ArrayList<>(N);
    for (int i = 0; i < N; ++i)
      AL.add(new ArrayList<>());
    AL.get(0).add(1); AL.get(0).add(6); // A->[B,G]
    AL.get(1).add(2); // B->C
    AL.get(2).add(3); AL.get(2).add(4); // C->[D,E]
    AL.get(3).add(0); // D->A
    AL.get(4).add(5); // E->F
    AL.get(5).add(0); AL.get(5).add(2); // F->[A,C]
    AL.get(6).add(5); // G->F
    ArrayList<Integer> ans = hierholzer(0);
    for (Integer u : ans)
      System.out.print((char)('A'+u) + " ");
    System.out.println();
  }
}
