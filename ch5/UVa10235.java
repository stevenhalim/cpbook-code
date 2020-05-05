// 2.788s in Java

import java.util.Scanner;
import java.math.BigInteger;

class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNext()) {
      int N = sc.nextInt(); System.out.printf("%d is ", N);
      BigInteger BN = BigInteger.valueOf(N);
      String R = new StringBuffer(BN.toString()).reverse().toString();
      int RN = Integer.parseInt(R);
      BigInteger BRN = BigInteger.valueOf(RN);
      if (!BN.isProbablePrime(10))               // certainty 10 is enough
        System.out.println("not prime.");
      else if ((N != RN) && BRN.isProbablePrime(10))
        System.out.println("emirp.");
      else
        System.out.println("prime.");
    }
  }
}



/*

// old (and longer) C++ code for comparison

#include <cstdio>
using namespace std;

int isPrime(long n) {
  long i;

  if (n <= 1) return 0;
  if (n == 2) return 1;
  if (n%2 == 0) return 0;

  for (i = 3; i*i <= n; i += 2)
    if (n%i == 0)
      return 0;

  return 1;
}

long reverse(long n) {
  long rev;
  for (rev = 0; n; n /= 10)
    rev = rev*10 + n%10;
  return rev;
}

int main() {
  long N;

  while (scanf("%ld",&N)!=EOF) {
    if (!isPrime(N)) printf("%ld is not prime.\n", N);
    else {
      if (N != reverse(N) && isPrime(reverse(N)))
        printf("%ld is emirp.\n", N);
      else printf("%ld is prime.\n", N);
    }
  }

  return 0;
}

*/
