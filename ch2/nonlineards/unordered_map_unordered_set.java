import java.util.*;

class unordered_map_unordered_set {
  public static void main(String[] args) {
    HashSet<Integer> used_values = new HashSet<>();
    HashMap<String, Integer> mapper = new HashMap<>();

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

    // then the internal content of mapper/used_values are not really known
    // (implementation dependent)

    // iterating through the content of mapper will give a jumbled output
    // as the keys are hashed into various slots
    System.out.println(mapper.keySet());
    System.out.println(mapper.values());

    // map can also be used like this
    System.out.println("steven's score is " + mapper.get("steven") + 
                       ", grace's score is " + mapper.get("grace"));
    System.out.println("==================");

    // there is no headSet and tailSet in an unordered_map

    // O(1) search, found
    System.out.println(used_values.contains(77)); // returns true
    // O(1) search, not found
    if (!used_values.contains(79))
      System.out.println("79 not found");
  }
}
