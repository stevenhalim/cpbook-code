import java.util.*;

class pair<X, Y> { // utilizing Java "Generics"
  X _first;
  Y _second;

  public pair(X f, Y s) { _first = f; _second = s; }

  X first() { return _first; }
  Y second() { return _second; }

  void setFirst(X f) { _first = f; }
  void setSecond(Y s) { _second = s; }
}

class priority_queue {
  public static void main(String[] args) {
    // introducing 'pair'
    PriorityQueue<pair<Integer, String>> pq = new PriorityQueue<>(1, 
      new Comparator<pair<Integer, String>>() { // overriding the compare method
        public int compare(pair<Integer, String> i, pair<Integer, String> j) {
          return j.first() - i.first(); // currently max heap, reverse these two to try produce min-heap
        }
      }
    );

    // suppose we enter these 7 money-name pairs below
    /*
    100 john
    10 billy
    20 andy
    100 steven
    70 felix
    2000 grace
    70 martin
    */
    pq.offer(new pair<Integer, String> (100, "john")); // inserting a pair in O(log n)
    pq.offer(new pair<Integer, String> (10, "billy"));
    pq.offer(new pair<Integer, String> (20, "andy"));
    pq.offer(new pair<Integer, String> (100, "steven"));
    pq.offer(new pair<Integer, String> (70, "felix"));
    pq.offer(new pair<Integer, String> (2000, "grace"));
    pq.offer(new pair<Integer, String> (70, "martin"));
    // this is how we use Java PriorityQueue
    // priority queue will arrange items in 'heap' based
    // on the first key in pair, which is money (integer), largest first
    // if first keys tied, use second key, which is name, largest first
  
    // the internal content of pq heap MAY be something like this:
    // re-read (max) heap concept if you do not understand this diagram
    // the primary keys are money (integer), secondary keys are names (string)!
    //                        (2000,grace)
    //           (100,steven)               (70,martin)   
    //     (100,john)   (10,billy)     (20,andy)  (70,felix)

    // let's print out the top 3 person with most money
    pair<Integer, String> result = pq.poll(); // O(1) to access the top / max element + O(log n) removal of the top and repair the structure
    System.out.println(result.second() + " has " + result.first() + " $");
    result = pq.poll();
    System.out.println(result.second() + " has " + result.first() + " $");
    result = pq.poll();
    System.out.println(result.second() + " has " + result.first() + " $");
  }
}
