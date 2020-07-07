import java.util.*;

class Main { /* UVa 11565 - Simple Equations */
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int N = sc.nextInt();
    while (N-- > 0) {
      int A = sc.nextInt(), B = sc.nextInt(), C = sc.nextInt();
      Boolean sol = false;
      int x, y, z;
      for (x = -22; (x <= 22) && !sol; ++x) if (x*x <= C)
        for (y = -100; (y <= 100) && !sol; ++y) if ((y != x) && (x*x + y*y <= C))
          for (z = -100; (z <= 100) && !sol; ++z)
            if ((z != x) && (z != y) &&
                (x+y+z == A) && (x*y*z == B) && (x*x + y*y + z*z == C)) {
              System.out.printf("%d %d %d\n", x, y, z);
              sol = true;
            }
      if (!sol) System.out.println("No solution.");
    }
  }
}
