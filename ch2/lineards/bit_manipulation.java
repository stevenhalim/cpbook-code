import java.util.*;

// note: for example usage of BitSet, see ch5/primes.java

class bit_manipulation {
  private static int setBit(int S, int j) { return S | (1 << j); }

  private static int isOn(int S, int j) { return S & (1 << j); }

  private static int clearBit(int S, int j) { return S & ~(1 << j); }

  private static int toggleBit(int S, int j) { return S ^ (1 << j); }

  private static int lowBit(int S) { return S & (-S); }

  private static int setAll(int n) { return (1 << n) - 1; }

  private static int modulo(int S, int N) { return ((S) & (N - 1)); } // returns S % N, where N is a power of 2

  private static int isPowerOfTwo(int S) { return (S & (S - 1)) == 0 ? 1 : 0; }

  private static int nearestPowerOfTwo(int S) { return 1 << Math.round(Math.log((double)S) / Math.log(2.0)); }

  private static int turnOffLastBit(int S) { return ((S) & (S - 1)); }

  private static int turnOnLastZero(int S) { return ((S) | (S + 1)); }

  private static int turnOffLastConsecutiveBits(int S) { return ((S) & (S + 1)); }

  private static int turnOnLastConsecutiveZeroes(int S) { return ((S) | (S - 1)); }

  private static void printSet(int vS) {             // in binary representation
    System.out.printf("S = %2d = ", vS);
    Stack<Integer> st = new Stack<Integer>();
    while (vS > 0) {
      st.push(vS % 2);
      vS /= 2;
    }
    while (!st.empty()) {                          // to reverse the print order
      System.out.printf("%d", st.peek());
      st.pop();
    }
    System.out.printf("\n");
  }

  public static void main(String[] args) {
    int S, T;

    System.out.printf("1. Representation (all indexing are 0-based and counted from right)\n");
    S = 34; printSet(S);
    System.out.printf("\n");

    System.out.printf("2. Multiply S by 2, then divide S by 4 (2x2), then by 2\n");
    S = 34; printSet(S);
    S = S << 1; printSet(S);
    S = S >> 2; printSet(S);
    S = S >> 1; printSet(S);
    System.out.printf("\n");

    System.out.printf("3. Set/turn on the 3-rd item of the set\n");
    S = 34; printSet(S);
    S = setBit(S, 3); printSet(S);
    System.out.printf("\n");

    System.out.printf("4. Check if the 3-rd and then 2-nd item of the set is on?\n");
    S = 42; printSet(S);
    T = isOn(S, 3); System.out.printf("T = %d, %s\n", T, T != 0 ? "ON" : "OFF");
    T = isOn(S, 2); System.out.printf("T = %d, %s\n", T, T != 0 ? "ON" : "OFF");
    System.out.printf("\n");

    System.out.printf("5. Clear/turn off the 1-st item of the set\n");
    S = 42; printSet(S);
    S = clearBit(S, 1); printSet(S);
    System.out.printf("\n");

    System.out.printf("6. Toggle the 2-nd item and then 3-rd item of the set\n");
    S = 40; printSet(S);
    S = toggleBit(S, 2); printSet(S);
    S = toggleBit(S, 3); printSet(S);
    System.out.printf("\n");

    System.out.printf("7. Check the first bit from right that is on\n");
    S = 40; printSet(S);
    T = lowBit(S); System.out.printf("T = %d (this is always a power of 2)\n", T);
    S = 52; printSet(S);
    T = lowBit(S); System.out.printf("T = %d (this is always a power of 2)\n", T);
    System.out.printf("\n");

    System.out.printf("8. Turn on all bits in a set of size n = 6\n");
    S = setAll(6); printSet(S);
    System.out.printf("\n");

    System.out.printf("9. Other tricks (not shown in the book)\n");
    System.out.printf("8 %% 4 = %d\n", modulo(8, 4));
    System.out.printf("7 %% 4 = %d\n", modulo(7, 4));
    System.out.printf("6 %% 4 = %d\n", modulo(6, 4));
    System.out.printf("5 %% 4 = %d\n", modulo(5, 4));
    System.out.printf("is %d power of two? %d\n", 9, isPowerOfTwo(9));
    System.out.printf("is %d power of two? %d\n", 8, isPowerOfTwo(8));
    System.out.printf("is %d power of two? %d\n", 7, isPowerOfTwo(7));
    for (int i = 1; i <= 16; i++)
      System.out.printf("Nearest power of two of %d is %d\n", i, nearestPowerOfTwo(i)); // special case for i == 0
    System.out.printf("S = %d, turn off last bit in S, S = %d\n", 40, turnOffLastBit(40));
    System.out.printf("S = %d, turn on last zero in S, S = %d\n", 41, turnOnLastZero(41));
    System.out.printf("S = %d, turn off last consecutive bits in S, S = %d\n", 39, turnOffLastConsecutiveBits(39));
    System.out.printf("S = %d, turn on last consecutive zeroes in S, S = %d\n", 36, turnOnLastConsecutiveZeroes(36));
  }
}
