import java.util.*;

class Main { /* Through the Desert */
  private static Vector<IntegerPair> events;

  private static Boolean can(double f) {
    int cur_d = 0, cur_n = 0, leak_rate = 0, dt = 0;
    double original_f = f;
    for (int i = 0; i < events.size(); ++i) {
      // for all events, consume this amount of fuel (0 amount if delta time is 0)
      dt = (events.get(i).first() - cur_d);
      f -=  dt / 100.0 * cur_n; // consumption
      f -= (dt) * leak_rate; // leak
      if (f < 0) // quick check
        return false;
      // change a parameter, if needed
      if (events.get(i).second() <= 0) // Fuel consumption n
        cur_n = -events.get(i).second();
      else if (events.get(i).second() == 1) // Leak
        ++leak_rate;
      else if (events.get(i).second() == 2) // Gas station
        f = original_f;
      else if (events.get(i).second() == 3) // Mechanic
        leak_rate = 0;
      else if (events.get(i).second() == 4) // Goal
        break;
      cur_d = events.get(i).first(); // update time
    }
    return (f >= 0.0); // if still have enough fuel by goal, this simulation is a success, otherwise, it is a failure
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (true) {
      int d = sc.nextInt(); sc.next(); sc.next(); // "0 Fuel consumption"
      int n = sc.nextInt();
      sc.nextLine();
      if (n == 0) break;
      events = new Vector<>();
      events.add(new IntegerPair(d, -n)); // first event, d = 0
      while (true) {
        d = sc.nextInt(); String line = sc.next();
        if (line.equals("Fuel")) {
          sc.next(); // "consumption"
          n = sc.nextInt();
          sc.nextLine();
          events.add(new IntegerPair(d, -n));
        }
        else if (line.equals("Leak"))
          events.add(new IntegerPair(d, 1));
        else if (line.equals("Gas")) {
          sc.nextLine(); // "Station"
          events.add(new IntegerPair(d, 2));
        }
        else if (line.equals("Mechanic"))
          events.add(new IntegerPair(d, 3));
        else if (line.equals("Goal")) {
          events.add(new IntegerPair(d, 4));
          break;
        }
      }
      double lo = 0.0, hi = 10000.0;
      for (int i = 0; i < 50; ++i) {             // log_2(10000/1e-9) ~= 43
        double mid = (lo+hi) / 2.0;              // looping 50x is enough
        if (can(mid))
          hi = mid;
        else
          lo = mid;
      }
      System.out.printf("%.3f\n", hi);           // this is the answer
    }
  }
}
