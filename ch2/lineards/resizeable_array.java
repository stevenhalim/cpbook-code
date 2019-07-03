import java.util.*;

class resizeable_array {
  public static void main(String[] args) {
    // initial value {7,7,7,0,0} and thus initial size (5)
    int[] arr = new int[] {7,7,7,0,0};
    // initial size (5) and initial value {5,5,5,5,5}
    ArrayList<Integer> v = new ArrayList<>(Collections.nCopies(5, 5));

    // 7 and 5, for Java ArrayList, we must use 'get'
    System.out.println("arr[2] = " + arr[2] + " and v[2] = " + v.get(2));

    for (int i = 0; i < 5; ++i) {
      arr[i] = i; // arr = {0,1,2,3,4}
      v.set(i, 7+i); // v = {7,8,9,10,11}, but for Java ArrayList, we must use 'set'
    }

    // 2 and 9
    System.out.println("arr[2] = " + arr[2] + " and v[2] = " + v.get(2));

    // arr[5] = 5; // static array will generate ArrayIndexOutOfBoundsException
    // // uncomment the line above to see the error

    v.add(77); // ArrayList resizes itself (use method add)
    System.out.println("v[5] = " + v.get(5)); // 77
  }
}
