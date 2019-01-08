import java.util.*;

class array_arraylist {
  public static void main(String[] args) {
    // initial value {7,7,7,0,0} and thus initial size (5)
    int[] arr = new int[] {7,7,7,0,0};
    // initial size (5) and initial value {5,5,5,5,5}
    ArrayList<Integer> v = new ArrayList<Integer>(Collections.nCopies(5, 5));

    // 7 and 5, for Java ArrayList, we must use 'get'
    System.out.println("arr[2] = " + arr[2] + " and v[2] = " + v.get(2));

    for (int i = 0; i <= 4; i++) {
      arr[i] = i;
      v.set(i, i);                 // for Java ArrayList, we must use 'set'
    }

    // 2 and 2
    System.out.println("arr[2] = " + arr[2] + " and v[2] = " + v.get(2));

    // arr[5] = 5;   // static array will generate index out of bound error
    // uncomment the line above to see the error

    v.add(5);                  // ArrayList resizes itself (use method add)
    System.out.println("v[5] = " + v.get(5));                          // 5
  }
}
