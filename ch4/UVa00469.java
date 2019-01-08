import java.util.*;
import java.text.*;

// classic DFS flood fill

class Main { /* UVa 469 - Wetlands of Florida, 0.659s in Java, 0.162s in C++ */
  private static String line;
  private static char[][] grid = new char[150][];
  private static int TC, R, C, row, col;

  private static int dr[] = {1,1,0,-1,-1,-1, 0, 1}; // S,SE,E,NE,N,NW,W,SW
  private static int dc[] = {0,1,1, 1, 0,-1,-1,-1}; // neighbors

  private static int floodfill(int r, int c, char c1, char c2) {
    if (r<0 || r>=R || c<0 || c>=C) return 0; // outside
    if (grid[r][c] != c1) return 0; // we want only c1
    grid[r][c] = c2; // important step to avoid cycling!
    int ans = 1; // coloring c1 -> c2, add 1 to answer
    for (int d = 0; d < 8; d++) // recurse to neighbors
      ans += floodfill(r + dr[d], c + dc[d], c1, c2);
    return ans;
  }

  // inside the void main(String[] args) of the solution for UVa 469 - Wetlands of Florida
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    // read the implicit graph as global 2D array 'grid'/R/C and (row, col) query coordinate
    TC = sc.nextInt(); sc.nextLine();
    sc.nextLine(); // remove dummy line

    while (TC-- > 0) {
      R = 0;
      while (true) {
        grid[R] = sc.nextLine().toCharArray();
        if (grid[R][0] != 'L' && grid[R][0] != 'W') // start of query
          break;
        R++;
      }
      C = grid[0].length;


      line = new String(grid[R]);
      while (true) {
        StringTokenizer st = new StringTokenizer(line);
        row = Integer.parseInt(st.nextToken()); row--; // index starts from 0!
        col = Integer.parseInt(st.nextToken()); col--;
        System.out.println(floodfill(row, col, 'W', '.')); // change water 'W' to '.'; count size of this lake
        floodfill(row, col, '.', 'W'); // restore for next query
        if (sc.hasNext()) line = sc.nextLine();
        else              break; // last test case
        if (line.length() == 0) break; // next test case
      }

      if (TC > 0)
        System.out.println();
    }
  }
}
