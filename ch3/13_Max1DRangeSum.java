import java.util.*;

class ch3_04_Max1DRangeSum {
  public static void main(String[] args) {
    int n = 9, A[] = { 4, -5, 4, -3, 4, 4, -4, 4, -5 };   // a sample array A
    int running_sum = 0, ans = 0;
    for (int i = 0; i < n; i++)                                       // O(n)
      if (running_sum + A[i] >= 0) {  // the overall running sum is still +ve
        running_sum += A[i];
        ans = Math.max(ans, running_sum);     // keep the largest RSQ overall
      }
      else        // the overall running sum is -ve, we greedily restart here
        running_sum = 0;      // because starting from 0 is better for future
                             // iterations than starting from -ve running sum
    System.out.printf("Max 1D Range Sum = %d\n", ans);         // should be 9
} }
