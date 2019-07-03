import java.util.*;

// This source code is not as complete as array_algorithms.cpp

class team implements Comparable<team> {
  private int id, solved, penalty;

  public team(int id, int solved, int penalty) {
    this.id = id;
    this.solved = solved;
    this.penalty = penalty;
  }

  public int compareTo(team o) {
    if (solved != o.solved) // can use this primary field to decide sorted order
      return o.solved - solved;   // ICPC rule: sort by number of problem solved
    else if (penalty != o.penalty)         // solved == o.solved, but we can use
                                       // secondary field to decide sorted order
      return penalty - o.penalty;       // ICPC rule: sort by descending penalty
    else                          // solved == o.solved AND penalty == o.penalty
      return id - o.id;                      // sort based on increasing team ID
  }

  public String toString() {
    return "id: " + id + ", solved: " + solved + ", penalty: " + penalty;
  }
}

class array_algorithms {
  public static void main(String[] args) {
    ArrayList<Integer> v = new ArrayList<>();

    v.add(10);
    v.add(7);
    v.add(2);
    v.add(15);
    v.add(4);

    // sort descending with vector
    Collections.sort(v);
    // if we want to modify comparison function, use the overloaded method: Collections.sort(List list, Comparator c);
    Collections.reverse(v);

    System.out.println(v);
    System.out.printf("==================\n");

    // shuffle the content again
    Collections.shuffle(v);
    System.out.println(v);
    System.out.printf("==================\n");

    // sort ascending
    Collections.sort(v);
    System.out.println(v);
    System.out.printf("==================\n");

    ArrayList<team> nus = new ArrayList<>();
    nus.add(new team(1, 1, 10));
    nus.add(new team(2, 3, 60));
    nus.add(new team(3, 1, 20));
    nus.add(new team(4, 3, 60));

    // without sorting, they will be ranked like this:
    for (int i = 0; i < 4; ++i)
      System.out.println(nus.get(i));

    Collections.sort(nus);              // sort using a comparison function
    System.out.printf("==================\n");
    // after sorting using ICPC rule, they will be ranked like this:
    for (int i = 0; i < 4; ++i)
      System.out.println(nus.get(i));
    System.out.printf("==================\n");

    int pos = Collections.binarySearch(v, 7);
    System.out.println("Trying to search for 7 in v, found at index = " + pos);

    pos = Collections.binarySearch(v, 77);
    System.out.println("Trying to search for 77 in v, found at index = " + pos); // output is -5 (explanation below)

    /*
    binarySearch will returns:
      index of the search key, if it is contained in the list;
      otherwise, (-(insertion point) - 1).
      The insertion point is defined as the point at which the key would be inserted into the list:
      the index of the first element greater than the key,
      or list.size(), if all elements in the list are less than the specified key.
      Note that this guarantees that the return value will be >= 0 if and only if the key is found. 
    */

    // sometimes these two useful simple macros are used
    System.out.printf("min(10, 7) = %d\n", Math.min(10, 7));
    System.out.printf("max(10, 7) = %d\n", Math.max(10, 7));
  }
}
