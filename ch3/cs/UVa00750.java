import java.util.*;

class Main { /* UVa 00750 - 8 Queens Chess Problem */
  private static int[] row = new int[9];
  private static int TC, a, b, lineCounter; // it is ok to use global variables in competitive programming

  private static boolean place(int col, int tryrow) {
    for (int prev = 1; prev < col; prev++) // check previously placed queens
      if (row[prev] == tryrow || (Math.abs(row[prev] - tryrow) == Math.abs(prev - col)))
        return false; // an infeasible solution if share same row or same diagonal
    return true;
  }

  private static void backtrack(int col) {
    for (int tryrow = 1; tryrow <= 8; tryrow++) // try all possible row
      if (place(col, tryrow)) { // if can place a queen at this col and row...
        row[col] = tryrow; // put this queen in this col and row
        if (col == 8 && row[b] == a) { // a candidate solution & (a, b) has 1 queen
          System.out.printf("%2d      %d", ++lineCounter, row[1]);
          for (int j = 2; j <= 8; j++) System.out.printf(" %d", row[j]);
          System.out.printf("\n");
        }
        else
          backtrack(col + 1); // recursively try next column
  }   }
  
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    TC = sc.nextInt();
    while (TC-- > 0) {
      a = sc.nextInt();
      b = sc.nextInt();
      for (int i = 0; i < 9; i++) row[i] = 0;
      lineCounter = 0;
      System.out.printf("SOLN       COLUMN\n");
      System.out.printf(" #      1 2 3 4 5 6 7 8\n\n");
      backtrack(1); // generate all possible 8! candidate solutions
      if (TC > 0) System.out.printf("\n");
    }
  }
}
