#include <bits/stdc++.h>                         // include all
using namespace std;
int main() {
  int N; scanf("%d\n", &N);
  while (N--) {                                  // loop from N,N-1,...,0
    char x[110];                                 // set size a bit larger
    scanf("0.%[0-9]...\n", &x);                  // `&' is optional here
    // note: if you are surprised with the technique above,
    // please check scanf details in www.cppreference.com
    printf("the digits are 0.%s\n", x);
  }
  return 0;
}
