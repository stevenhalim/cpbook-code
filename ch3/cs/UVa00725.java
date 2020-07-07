import java.util.*;

class Main { /* UVa 00725 - Division */
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    Boolean first = true;
    while (true) {
      int N = sc.nextInt();
      if (N == 0) break;
      if (!first) System.out.println();
      first = false;
      Boolean noSolution = true;
      for (int fghij = 1234; fghij <= 98765/N; ++fghij) {
        int abcde = fghij*N; // this way, abcde and fghij are at most 5 digits
        int tmp, used = (fghij < 10000) ? 1 : 0; // if digit f=0, then we have to flag it
        tmp = abcde; while (tmp > 0) { used |= 1<<(tmp%10); tmp /= 10; }
        tmp = fghij; while (tmp > 0) { used |= 1<<(tmp%10); tmp /= 10; }
        if (used == (1<<10)-1) { // if all digits are used, print it
          System.out.printf("%05d / %05d = %d\n", abcde, fghij, N);
          noSolution = false;
        }
      }
      if (noSolution) System.out.printf("There are no solutions for %d.\n", N);
    }
  }
}
