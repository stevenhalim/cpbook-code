import java.util.*;

class Main { /* UVa 00441 - Lotto */
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    Boolean first = true;
    while (true) {
      int k = sc.nextInt();
      if (k == 0) break;
      if (!first) System.out.println();
      first = false;
      int[] S = new int[16];
      for (int i = 0; i < k; ++i) S[i] = sc.nextInt(); // input: k sorted ints
      for (int a = 0  ; a < k-5; ++a)            // six nested loops!
        for (int b = a+1; b < k-4; ++b)
          for (int c = b+1; c < k-3; ++c)
            for (int d = c+1; d < k-2; ++d)
              for (int e = d+1; e < k-1; ++e)
                for (int f = e+1; f < k  ; ++f)
                  System.out.printf("%d %d %d %d %d %d\n",S[a],S[b],S[c],S[d],S[e],S[f]);
    }
  }
}
