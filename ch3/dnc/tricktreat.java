import java.io.*;
import java.util.*;

class tricktreat { /* Trick or Treat */
  private static final int MAX_n = 50010;
  private static final double INF = 1e9;

  private static int n;
  private static double[] xs = new double[MAX_n], ys = new double[MAX_n]; // big, just make it global

  private static double f(double x) { // square of earliest meeting time if all n kids meet at coordinate (x, y = 0.0)
    double ans = -INF;
    for (int i = 0; i < n; ++i) // all n kids dash to (x, y = 0.0)
      ans = Math.max(ans, (xs[i]-x) * (xs[i]-x) + ys[i] * ys[i]); // avoid computing sqrt which is slow
    return ans;
  }

  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(      // use BufferedReader
      new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(            // and PrintWriter
      new BufferedWriter(new OutputStreamWriter(System.out))); // = fast IO
    String[] tokens;
    while (true) {
      n = Integer.parseInt(br.readLine());
      if (n == 0) break;
      double lo = INF, hi = -INF;
      for (int i = 0; i < n; ++i) {
        tokens = br.readLine().split(" ");
        xs[i] = Double.parseDouble(tokens[0]);
        ys[i] = Double.parseDouble(tokens[1]);
        lo = Math.min(lo, xs[i]);
        hi = Math.max(hi, xs[i]);
      }
      br.readLine();                             // skip dummy line
      for (int i = 0; i < 50; ++i) {             // similar as BSTA
        double delta = (hi-lo)/3.0;              // 1/3rd of the range
        double m1 = lo+delta;                    // 1/3rd away from lo
        double m2 = hi-delta;                    // 1/3rd away from hi
        if (f(m1) > f(m2))                       // f is unimodal
          lo = m1;
        else
          hi = m2;
      }
      pw.printf("%.10f %.10f\n", lo, Math.sqrt(f(lo)));
    }
    pw.close();
  }
}
