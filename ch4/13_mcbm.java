import java.util.*;
import java.text.*;

class ch4_09_mcbm {
  private static Vector < Vector < Integer > > AdjList = 
    new Vector < Vector < Integer > >();
  private static Vector < Integer > match, visited; // global variables

  private static int Aug(int l) {
    if (visited.get(l) == 1) return 0;
    visited.set(l, 1);

    Iterator it = AdjList.get(l).iterator();
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
    int i, j;

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
    AdjList.clear();
    for (i = 0; i < V; i++) {
      Vector<Integer> Neighbor = new Vector<Integer>();
      AdjList.add(Neighbor); // store blank vector first
    }
    
    for (i = 0; i < V_l; i++)
      for (j = 0; j < 3; j++)
        if (isprime(set1[i] + set2[j]))
          AdjList.get(i).add(3 + j);
*/

    // For bipartite graph in Figure 4.44, V = 5, Vleft = 3 (vertex 0 unused)
    // AdjList[0] = {} // dummy vertex, but you can choose to use this vertex
    // AdjList[1] = {3, 4}
    // AdjList[2] = {3}
    // AdjList[3] = {}   // we use directed edges from left to right set only
    // AdjList[4] = {}

    int V = 5, V_l = 3;
    AdjList.clear();
    for (i = 0; i < V; i++) {
      Vector<Integer> Neighbor = new Vector<Integer>();
      AdjList.add(Neighbor); // store blank vector first
    }
    AdjList.get(1).add(3);
    AdjList.get(1).add(4);
    AdjList.get(2).add(3);

    int MCBM = 0;
    match = new Vector < Integer > ();
    match.addAll(Collections.nCopies(V, -1));
    for (int l = 0; l < V_l; l++) {
      visited = new Vector < Integer > ();
      visited.addAll(Collections.nCopies(V_l, 0));
      MCBM += Aug(l);
    }
    System.out.printf("Found %d matchings\n", MCBM);
  }
}
