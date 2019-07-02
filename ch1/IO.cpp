#include <bits/stdc++.h>
using namespace std;

int main() {
  // comment all lines and only uncomment demo code that you are interested with
  
  freopen("IO_in1.txt", "r", stdin);
  int TC;
  scanf("%d", &TC); // number of test cases
  while (TC--) { // shortcut to repeat until 0
    int a, b; scanf("%d %d", &a, &b);
    printf("%d\n", a+b); // compute on the fly
  }

  // freopen("IO_in2.txt", "r", stdin);
  // int a, b;
  // // stop when both integers are 0
  // while (scanf("%d %d", &a, &b), (a || b))
  //   printf("%d\n", a+b);

  // freopen("IO_in3.txt", "r", stdin);
  // int a, b;
  // // scanf returns the number of items read
  // while (scanf("%d %d", &a, &b) == 2)
  // // or you can check for EOF, i.e.
  // // while (scanf("%d %d", &a, &b) != EOF)
  //   printf("%d\n", a+b);

  // freopen("IO_in3.txt", "r", stdin); // same input file as before
  // int a, b, c = 0;
  // while (scanf("%d %d", &a, &b) != EOF)
  //   // notice the two '\n'
  //   printf("Case %d: %d\n\n", ++c, a+b);

  // freopen("IO_in3.txt", "r", stdin); // same input file as before
  // int a, b, c = 0;
  // while (scanf("%d %d", &a, &b) != EOF) {
  //   if (c > 0) printf("\n"); // 2nd/more cases
  //   printf("Case %d: %d\n", ++c, a+b);
  // }

  // freopen("IO_in4.txt", "r", stdin);
  // int k;
  // while (scanf("%d", &k) != EOF) {
  //   int ans = 0, v;
  //   while (k--) { scanf("%d", &v); ans += v; }
  //   printf("%d\n", ans);
  // }

  // freopen("IO_in5.txt", "r", stdin);
  // while (1) { // keep looping
  //   int ans = 0, v;
  //   char dummy;
  //   while (scanf("%d%c", &v, &dummy) != EOF) {
  //     ans += v;
  //     if (dummy == '\n') break; // test EOLN
  //   }
  //   if (feof(stdin)) break; // test EOF
  //   printf("%d\n", ans);
  // }

  return 0;
}
