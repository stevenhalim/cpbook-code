// Beverages

import java.util.*;

class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int caseNo = 0;

    while (true) {
      String line = sc.nextLine();
      int N = Integer.parseInt(line);
      ArrayList<ArrayList<Integer>> AL = new ArrayList<>();
      for (int i = 0; i < N; ++i)
        AL.add(new ArrayList<>());
      HashMap<String, Integer> mapper = new HashMap<>();
      HashMap<Integer, String> reverseMapper = new HashMap<>();
      for (int i = 0; i < N; ++i) {
        String B1 = sc.nextLine();
        mapper.put(B1, i);                       // give index i to B1
        reverseMapper.put(i, B1);
      }

      ArrayList<Integer> in_degree = new ArrayList<>(Collections.nCopies(N, 0));
      int M = Integer.parseInt(sc.nextLine());
      for (int i = 0; i < M; ++i) {
        String[] token = sc.nextLine().split(" ");
        String B1 = token[0], B2 = token[1];
        int a = mapper.get(B1), b = mapper.get(B2);
        AL.get(a).add(b);                        // directed edge
        in_degree.set(b, in_degree.get(b)+1);
      }

      System.out.printf("Case #%d: Dilbert should drink beverages in this order:", ++caseNo);

      // enqueue vertices with zero incoming degree into a (priority) queue pq
      PriorityQueue<Integer> pq = new PriorityQueue<>(); // min priority queue
      for (int u = 0; u < N; ++u)
        if (in_degree.get(u) == 0)               // next to be processed
          pq.add(u);                             // smaller index first

      while (!pq.isEmpty()) {                    // Kahn's algorithm
        int u = pq.poll();
        System.out.printf(" %s", reverseMapper.get(u)); // process u here
        for (Integer v : AL.get(u)) {
          in_degree.set(v, in_degree.get(v)-1);  // virtually remove u->v
          if (in_degree.get(v) > 0) continue;    // not a candidate, skip
          pq.add(v);                             // enqueue v in pq
        }
      }

      System.out.printf(".\n\n");
      if (!sc.hasNext()) break;
      sc.nextLine(); // dummy
    }
  }
}
