// Wetlands of Florida
// classic DFS flood fill

#include <bits/stdc++.h>
using namespace std;

char line[150], grid[150][150];
int TC, R, C, row, col;

int dr[] = { 1, 1, 0,-1,-1,-1, 0, 1};           // trick to explore 2D grid
int dc[] = { 0, 1, 1, 1, 0,-1,-1,-1};      // S,SE,E,NE,N,NW,W,SW neighbors

int floodfill(int r, int c, char c1, char c2) {   // returns the size of CC
  if (r < 0 || r >= R || c < 0 || c >= C) return 0;         // outside grid
  if (grid[r][c] != c1) return 0;                 // does not have color c1
  int ans = 1;   // adds 1 to ans because vertex (r, c) has c1 as its color
  grid[r][c] = c2;    // now recolors vertex (r, c) to c2 to avoid cycling!
  for (int d = 0; d < 8; ++d)
    ans += floodfill(r+dr[d], c+dc[d], c1, c2);
  return ans;                   // the code is neat as we use dr[] and dc[]
}

// inside the int main() of the solution for UVa 469 - Wetlands of Florida
int main() {
  // read the implicit graph as global 2D array 'grid'/R/C and (row, col) query coordinate
  sscanf(gets(line), "%d", &TC);
  gets(line); // remove dummy line

  while (TC--) {
    R = 0;
    while (1) {
      gets(grid[R]);
      if (grid[R][0] != 'L' && grid[R][0] != 'W') // start of query
        break;
      ++R;
    }
    C = (int)strlen(grid[0]);

    strcpy(line, grid[R]);
    while (1) {
      sscanf(line, "%d %d", &row, &col); row--; col--; // index starts from 0!
      printf("%d\n", floodfill(row, col, 'W', '.')); // change water 'W' to '.'; count size of this lake
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
