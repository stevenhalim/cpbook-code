import java.util.*;

class QuickSelect {
  static int Partition(int A[], int l, int r) {
    int p = A[l];                                // p is the pivot
    int m = l;                                   // S1 and S2 are empty
    int temp;
    for (int k = l+1; k <= r; ++k) {             // explore unknown region
      if (A[k] < p) {                            // case 2
        m++;
        temp = A[k]; A[k] = A[m]; A[m] = temp;
      } // notice that we do nothing in case 1: a[k] >= p
    }
    temp = A[l]; A[l] = A[m]; A[m] = temp;       // swap pivot with a[m]
    return m;                                    // return pivot index
  }

  static int RandPartition(int[] A, int l, int r) {
    Random rnd = new Random();
    int p = l + rnd.nextInt(r-l+1);              // select a random pivot
    int temp = A[l]; A[l] = A[p]; A[p] = temp;   // swap A[p] with A[l]
    return Partition(A, l, r);
  }

  static int QuickSelect(int[] A, int l, int r, int k) {
    if (l == r) return A[l];
    int q = RandPartition(A, l, r);
    if (q+1 == k)
      return A[q];
    else if (q+1 > k)
      return QuickSelect(A, l, q-1, k);
    else
      return QuickSelect(A, q+1, r, k);
  }

  public static void main(String[] args) {
    int[] A = new int[] { 2, 8, 7, 1, 5, 4, 6, 3 }; // permutation of [1..8]

    System.out.println(QuickSelect(A, 0, 7, 8)); // the output must be 8
    System.out.println(QuickSelect(A, 0, 7, 7)); // the output must be 7
    System.out.println(QuickSelect(A, 0, 7, 6)); // the output must be 6
    System.out.println(QuickSelect(A, 0, 7, 5)); // the output must be 5
    System.out.println(QuickSelect(A, 0, 7, 4)); // the output must be 4
    System.out.println(QuickSelect(A, 0, 7, 3)); // the output must be 3
    System.out.println(QuickSelect(A, 0, 7, 2)); // the output must be 2
    System.out.println(QuickSelect(A, 0, 7, 1)); // the output must be 1

    // try experimenting with the content of array A to see the behavior of "QuickSelect"
  }
}
