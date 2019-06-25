// Simple Equations

#include <bits/stdc++.h>
using namespace std;

int main() {
  int N; scanf("%d", &N);
  while (N--) {
    int A, B, C; scanf("%d %d %d", &A, &B, &C);
    // 0.150s
    // bool sol = false; int x, y, z;
    // for (x = -100; x <= 100; ++x)                    // ~201^3 ~= 8M operations
    //   for (y = -100; y <= 100; ++y)
    //     for (z = -100; z <= 100; ++z)
    //       if ((y != x) && (z != x) && (z != y) &&    // all 3 must be different
    //           (x+y+z == A) && (x*y*z == B) && (x*x + y*y + z*z == C)) {
    //         if (!sol) printf("%d %d %d\n", x, y, z);
    //         sol = true;
    //       }
    // 0.000s, when x is reduced to -22 to 22 due to x*y*z = B and x <= y <= z so x^3 <= B or x <= B^(1/3)
    bool sol = false; int x, y, z;
    for (x = -22; (x <= 22) && !sol; ++x) if (x*x <= C)
      for (y = -100; (y <= 100) && !sol; ++y) if ((y != x) && (x*x + y*y <= C))
        for (z = -100; (z <= 100) && !sol; ++z)
          if ((z != x) && (z != y) &&
              (x+y+z == A) && (x*y*z == B) && (x*x + y*y + z*z == C)) {
            printf("%d %d %d\n", x, y, z);
            sol = true;
          }
    if (!sol) printf("No solution.\n");
  }
  return 0;
}
