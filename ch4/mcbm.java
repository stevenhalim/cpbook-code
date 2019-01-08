import java.util.*;
import java.text.*;

class mcbm {
  private static ArrayList<ArrayList<Integer>> AL = new ArrayList<>();
  private static ArrayList<Integer> match, visited; // global variables

  private static int Aug(int l) {
    if (visited.get(l) == 1) return 0;
    visited.set(l, 1);

    Iterator it = AL.get(l).iterator();
    while (it.hasNext()) { // either greedy assignment or recurse
      Integer right = (Integer)it.next();
      if (match.get(right) == -1 || Aug(match.get(right)) == 1) {
        match.set(right, l);
        return 1; // we found one matching
      }
    }

    return 0; // no matching
  }

  private static Boolean isprime(int v) {
    int primes[] = new int[] {2,3,5,7,11,13,17,19,23,29};
    for (int i = 0; i < 10; i++)
      if (primes[i] == v)
        return true;
    return false;
  }

  public static void main(String[] args) {
/*
    // Graph in Figure 4.40 can be built on the fly
    // we know there are 6 vertices in this bipartite graph, l side are numbered 0,1,2, right side 3,4,5
    //int V = 6, V_l = 3;
    //int set1[] = new int[] {1,7,11}, set2[] = new int[] {4,10,12};

    // Graph in Figure 4.41 can be built on the fly
    // we know there are 5 vertices in this bipartite graph, l side are numbered 0,1, right side 3,4,5
    int V = 5, V_l = 2;
    int set1[] = new int[] {1,7}, set2[] = new int[] {4,10,12};

    // build the bipartite graph, only directed edge from l to right is needed
    AL.clear();
    for (i = 0; i < V; i++) {
      ArrayList<Integer> Neighbor = new ArrayList<Integer>();
      AL.add(Neighbor); // store blank ArrayList first
    }
    
    for (i = 0; i < V_l; i++)
      for (j = 0; j < 3; j++)
        if (isprime(set1[i] + set2[j]))
          AL.get(i).add(3 + j);
*/

    // For bipartite graph in Figure 4.44, V = 5, Vleft = 3 (vertex 0 unused)
    // AL[0] = {} // dummy vertex, but you can choose to use this vertex
    // AL[1] = {3, 4}
    // AL[2] = {3}
    // AL[3] = {}   // we use directed edges from left to right set only
    // AL[4] = {}

    int V = 5, V_l = 3;
    AL.clear();
    for (int i = 0; i < V; i++) {
      ArrayList<Integer> Neighbor = new ArrayList<Integer>();
      AL.add(Neighbor); // store blank ArrayList first
    }
    AL.get(1).add(3);
    AL.get(1).add(4);
    AL.get(2).add(3);

    int MCBM = 0;
    match = new ArrayList < Integer > ();
    match.addAll(Collections.nCopies(V, -1));
    for (int l = 0; l < V_l; l++) {
      visited = new ArrayList < Integer > ();
      visited.addAll(Collections.nCopies(V_l, 0));
      MCBM += Aug(l);
    }
    System.out.printf("Found %d matchings\n", MCBM);
  }
}
