// Simple Equations

#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("test.txt", "r", stdin);
  int N; scanf("%d", &N);
  while (N--) {
    int A, B, C; scanf("%d %d %d", &A, &B, &C);
    bool sol = false;
    //// 0.408 s
    //for (int x = -100; x <= 100; x++) // up to 201^3 ~= 8M operations per test case
    //  for (int y = -100; y <= 100; y++)
    //    for (int z = -100; z <= 100; z++)
    //      if (x != y && x != z && y != z &&          // all three must be different
    //          x + y + z == A && x * y * z == B && x * x + y * y + z * z == C) {
    //        if (!sol) printf("%d %d %d\n", x, y, z);
    //        sol = true;
    //      }
    // 0.036 s, change to 0.020s if x is reduced to -22 to 22 due to x*y*z = B and x<=y<=z so x^3 <= B or x <= B^(1/3)
    for (int x = -100; x <= 100 && !sol; x++) if (x*x <= C)
      for (int y = -100; y <= 100 && !sol; y++) if (y!=x && x*x + y*y <= C)
        for (int z = -100; z <= 100 && !sol; z++)
          if (z != y && z != x &&
              x + y + z == A && x * y * z == B && x * x + y * y + z * z == C) {
            printf("%d %d %d\n", x, y, z);
            sol = true;
          }
    if (!sol) printf("No solution.\n");
  }
  return 0;
}
