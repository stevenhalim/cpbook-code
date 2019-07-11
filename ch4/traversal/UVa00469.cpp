// Wetlands of Florida
// classic DFS flood fill

#include <bits/stdc++.h>
using namespace std;

char line[150], grid[150][150];
int R, C;

int dr[] = { 1, 1, 0,-1,-1,-1, 0, 1};            // the order is:
int dc[] = { 0, 1, 1, 1, 0,-1,-1,-1};            // S/SE/E/NE/N/NW/W/SW

int floodfill(int r, int c, char c1, char c2) {  // returns the size of CC
  if ((r < 0) || (r >= R) || (c < 0) || (c >= C)) return 0; // outside grid
  if (grid[r][c] != c1) return 0;                // does not have color c1
  int ans = 1;                                   // (r, c) has color c1
  grid[r][c] = c2;                               // to avoid cycling
  for (int d = 0; d < 8; ++d)
    ans += floodfill(r+dr[d], c+dc[d], c1, c2);  // the code is neat as
  return ans;                                    // we use dr[] and dc[]
}

// inside int main()
int main() {
  // read the grid as a global 2D array + read (row, col) query coordinates
  int TC; sscanf(gets(line), "%d", &TC);
  gets(line); // remove dummy line

  while (TC--) {
    R = 0;
    while (1) {
      gets(grid[R]);
      if ((grid[R][0] != 'L') && (grid[R][0] != 'W')) // start of query
        break;
      ++R;
    }
    C = (int)strlen(grid[0]);

    strcpy(line, grid[R]);
    while (1) {
      int row, col; sscanf(line, "%d %d", &row, &col); row--; col--; // index starts from 0!
      printf("%d\n", floodfill(row, col, 'W', '.')); // count size of wet area
      floodfill(row, col, '.', 'W'); // restore for next query
      gets(line);
      if (strcmp(line, "") == 0 || feof(stdin)) // next test case or last test case
        break;
    }

    if (TC)
      printf("\n");
  }

  return 0;
}
