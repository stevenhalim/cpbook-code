#include <bits/stdc++.h>
using namespace std;

int main() {
  // comment all lines and only uncomment demo code that you are interested with
  
  freopen("04_in1.txt", "r", stdin);
  int TC, a, b;
  scanf("%d", &TC); // number of test cases
  while (TC--) { // shortcut to repeat until 0
    scanf("%d %d", &a, &b); // compute answer
    printf("%d\n", a+b); // on the fly
  }

  // freopen("04_in2.txt", "r", stdin);
  // int a, b;
  // // stop when both integers are 0
  // while (scanf("%d %d", &a, &b), (a || b))
  //   printf("%d\n", a+b);

  // freopen("04_in3.txt", "r", stdin);
  // int a, b;
  // // scanf returns the number of items read
  // while (scanf("%d %d", &a, &b) == 2)
  // // or you can check for EOF, i.e.
  // // while (scanf("%d %d", &a, &b) != EOF)
  //   printf("%d\n", a+b);

  // freopen("04_in3.txt", "r", stdin); // same input file as before
  // int a, b, c = 1;
  // while (scanf("%d %d", &a, &b) != EOF)
  //   // notice the two '\n'
  //   printf("Case %d: %d\n\n", c++, a+b);

  // freopen("04_in3.txt", "r", stdin); // same input file as before
  // int a, b, c = 1;
  // while (scanf("%d %d", &a, &b) != EOF) {
  //   if (c > 1) printf("\n"); // 2nd/more cases
  //   printf("Case %d: %d\n", c++, a+b);
  // }

  // freopen("04_in4.txt", "r", stdin);
  // int k, ans, v;
  // while (scanf("%d", &k) != EOF) {
  //   ans = 0;
  //   while (k--) { scanf("%d", &v); ans += v; }
  //   printf("%d\n", ans);
  // }

  // freopen("04_in5.txt", "r", stdin);
  // int ans, v;
  // char dummy;
  // while (1) { // keep looping
  //   ans = 0;
  //   while (scanf("%d%c", &v, &dummy) != EOF) {
  //     ans += v;
  //     if (dummy == '\n') break; } // test EOLN
  //   if (feof(stdin)) break; // test EOF
  //   printf("%d\n", ans);
  // }

  return 0;
}
