import java.util.*;

class grass_UVa10382 { /* Watering Grass */
  private static final double EPS = 1e-9;

  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNext()) {
      int n = sc.nextInt(), l = sc.nextInt(), w = sc.nextInt();
      ArrayList<sp> sprinkler = new ArrayList<>();
      for (int i = 0; i < n; ++i) {
        int x = sc.nextInt(), r = sc.nextInt();
        if (2*r >= w) {
          double d_x = Math.sqrt((double)r*r - (w/2.0)*(w/2.0));
          sprinkler.add(new sp(x-d_x, x+d_x)); // sort based on smaller x_l and then larger x_r
        }
        else
          sprinkler.add(new sp((double)x-EPS, (double)x+EPS)); // to make this unselected...
      }
   
      Collections.sort(sprinkler);               // sort the sprinklers
      Boolean possible = true;
      double covered = 0.0;
      int ans = 0;
      for (int i = 0; (i < n) && possible; ++i) {
        if (covered > l) break;                  // done
        if (sprinkler.get(i).x_r() < covered+EPS) continue; // inside prev interval
        if (sprinkler.get(i).x_l() < covered+EPS) { // can cover
          double max_r = -1.0;
          int max_id = -1;
          for (int j = i; (j < n) && (sprinkler.get(j).x_l() < covered+EPS); ++j)
            if (sprinkler.get(j).x_r() > max_r) { // go to right to find
              max_r = sprinkler.get(j).x_r();    // interval with
              max_id = j;                        // the largest coverage
            }
          ++ans;
          covered = max_r;                       // jump here
          i = max_id;
        }
        else
          possible = false;
      }
      if (!possible || (covered < l))
        System.out.println(-1);
      else
        System.out.println(ans);
    }
  }
}

class sp implements Comparable<sp> {             // int: x, r; double: x_l, x_r
  Double _x_l, _x_r;

  public sp(Double x_l, Double x_r) {
    _x_l = x_l;
    _x_r = x_r;
  }

  public int compareTo(sp o) {
    if (Math.abs(this.x_l() - o.x_l()) > 1e-9)
      return this.x_l() - o.x_l() > 0 ? 1 : -1;
    else if (Math.abs(this.x_r() - o.x_r()) > 1e-9)
      return this.x_r() - o.x_r() > 0 ? -1 : 1;
    return 0;
  }

  Double x_l() { return _x_l; }
  Double x_r() { return _x_r; }
}
