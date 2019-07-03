import java.util.*;

class map_set {
  public static void main(String[] args) {
    // note: there are many clever usages of this set/map
    // that you can learn by looking at top coder's codes
    TreeSet<Integer> used_values = new TreeSet<>(); // must use TreeSet as Set is an abstract class
    TreeMap<String, Integer> mapper = new TreeMap<>(); // must use TreeMap as Map is an abstract class

    // suppose we enter these 7 name-score pairs below
    /*
    john 78
    billy 69
    andy 80
    steven 77
    felix 82
    grace 75
    martin 81
    */
    mapper.put("john", 78);   used_values.add(78);
    mapper.put("billy", 69);  used_values.add(69);
    mapper.put("andy", 80);   used_values.add(80);
    mapper.put("steven", 77); used_values.add(77);
    mapper.put("felix", 82);  used_values.add(82);
    mapper.put("grace", 75);  used_values.add(75);
    mapper.put("martin", 81); used_values.add(81);

    // then the internal content of mapper MAY be something like this:
    // re-read balanced BST concept if you do not understand this diagram
    // the keys are names (string)!
    //                        (grace,75) 
    //           (billy,69)               (martin,81)   
    //     (andy,80)   (felix,82)    (john,78)  (steven,77)

    // iterating through the content of mapper will give a sorted output
    // based on keys (names)
    System.out.println(mapper.keySet());
    System.out.println(mapper.values());

    // map can also be used like this
    System.out.println("steven's score is " + mapper.get("steven") + ", grace's score is " + mapper.get("grace"));
    System.out.println("==================");

    // interesting usage of SubMap
    // display data between ["f".."m") ('felix' is included, martin' is excluded)
    SortedMap<String, Integer> res = mapper.subMap("f", "m");
    System.out.println(res.keySet());
    System.out.println(res.values());

    // the internal content of used_values MAY be something like this
    // the keys are values (integers)!
    //                 (78) 
    //         (75)            (81)   
    //     (69)    (77)    (80)    (82)

    // O(log n) search, found
    System.out.println(used_values.contains(77)); // returns true
    System.out.println(used_values.headSet(77)); // returns [69, 75] (these two are before 77 in the inorder traversal of this BST)
    System.out.println(used_values.tailSet(77)); // returns [77, 78, 80, 81, 82] (these five are equal or after 77 in the inorder traversal of this BST)
    // O(log n) search, not found
    if (!used_values.contains(79))
      System.out.println("79 not found");
  }
}
