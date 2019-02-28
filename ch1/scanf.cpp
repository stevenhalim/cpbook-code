#include <bits/stdc++.h>
using namespace std;

char x[110]; // make it a habit to set array size a bit larger than needed

int main() {
  int N; scanf("%d\n", &N);
  while (N--) {                                  // from N, N-1, ..., 0
    scanf("0.%[0-9]...\n", &x); // `&' is optional when x is a char array
    // note: if you are surprised with the technique above,
    // please check scanf details in www.cppreference.com
    printf("the digits are 0.%s\n", x);
  }
}
