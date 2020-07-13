// note: for example usage of bitset, see ch5/primes.cpp

#include <bits/stdc++.h>
using namespace std;

#define isOn(S, j) (S & (1<<j))
#define setBit(S, j) (S |= (1<<j))
#define clearBit(S, j) (S &= ~(1<<j))
#define toggleBit(S, j) (S ^= (1<<j))
#define lowBit(S) (S & (-S))
#define setAll(S, n) (S = (1<<n)-1)

#define modulo(S, N) ((S) & (N-1))   // returns S % N, where N is a power of 2
#define isPowerOfTwo(S) (!(S & (S-1)))
#define nearestPowerOfTwo(S) (1<<lround(log2(S)))
#define turnOffLastBit(S) ((S) & (S-1))
#define turnOnLastZero(S) ((S) | (S+1))
#define turnOffLastConsecutiveBits(S) ((S) & (S+1))
#define turnOnLastConsecutiveZeroes(S) ((S) | (S-1))

void printSet(int vS) {                         // in binary representation
  printf("S = %2d = ", vS);
  stack<int> st;
  while (vS)
    st.push(vS%2), vS /= 2;
  while (!st.empty())                         // to reverse the print order
    printf("%d", st.top()), st.pop();
  printf("\n");
}

int main() {
  int S, T;

  printf("1. Representation (all indexing are 0-based and counted from right)\n");
  S = 34; printSet(S);
  printf("\n");

  printf("2. Multiply S by 2, then divide S by 4 (2x2), then by 2\n");
  S = 34; printSet(S);
  S = S << 1; printSet(S);
  S = S >> 2; printSet(S);
  S = S >> 1; printSet(S);
  printf("\n");

  printf("3. Set/turn on the 3-rd item of the set\n");
  S = 34; printSet(S);
  setBit(S, 3); printSet(S);
  printf("\n");

  printf("4. Check if the 3-rd and then 2-nd item of the set is on?\n");
  S = 42; printSet(S);
  T = isOn(S, 3); printf("T = %d, %s\n", T, T ? "ON" : "OFF");
  T = isOn(S, 2); printf("T = %d, %s\n", T, T ? "ON" : "OFF");
  printf("\n");

  printf("5. Clear/turn off the 1-st item of the set\n");
  S = 42; printSet(S);
  clearBit(S, 1); printSet(S);
  printf("\n");

  printf("6. Toggle the 2-nd item and then 3-rd item of the set\n");
  S = 40; printSet(S);
  toggleBit(S, 2); printSet(S);
  toggleBit(S, 3); printSet(S);
  printf("\n");

  printf("7. Check the first bit from right that is on\n");
  S = 40; printSet(S);
  T = lowBit(S); printf("T = %d (this is always a power of 2)\n", T);
  S = 52; printSet(S);
  T = lowBit(S); printf("T = %d (this is always a power of 2)\n", T);
  printf("\n");

  printf("8. Turn on all bits in a set of size n = 6\n");
  setAll(S, 6); printSet(S);
  printf("\n");

  printf("9. Other tricks (not shown in the book)\n");
  printf("8 %% 4 = %d\n", modulo(8, 4));
  printf("7 %% 4 = %d\n", modulo(7, 4));
  printf("6 %% 4 = %d\n", modulo(6, 4));
  printf("5 %% 4 = %d\n", modulo(5, 4));
  printf("is %d power of two? %d\n", 9, isPowerOfTwo(9));
  printf("is %d power of two? %d\n", 8, isPowerOfTwo(8));
  printf("is %d power of two? %d\n", 7, isPowerOfTwo(7));
  for (int i = 1; i <= 16; i++)
    printf("Nearest power of two of %d is %d\n", i, nearestPowerOfTwo(i)); // special case for i == 0
  printf("S = %d, turn off last bit in S, S = %d\n", 40, turnOffLastBit(40));
  printf("S = %d, turn on last zero in S, S = %d\n", 41, turnOnLastZero(41));
  printf("S = %d, turn off last consecutive bits in S, S = %d\n", 39, turnOffLastConsecutiveBits(39));
  printf("S = %d, turn on last consecutive zeroes in S, S = %d\n", 36, turnOnLastConsecutiveZeroes(36));

  return 0;
}
