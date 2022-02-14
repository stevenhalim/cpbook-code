import java.io.*;
import java.util.*;

// (Nearly) 1-1 translation of maxflow.cpp with min-cut augmentation
class Pair {
    int first, second;

    Pair(int first, int second) {
        this.first = first;
        this.second = second;
    }
}

class Edge {
    int v;
    long w, f;

    Edge(int v, long w, long f) {
        this.v = v;
        this.w = w;
        this.f = f;
    }
}

public class maxflow {
    static long INF = 1000000000000000000l;

    int V;
    Edge[] EL;
    int ELSize;
    List<List<Integer>> AL;
    int[] d, last;
    Pair[] p;

    maxflow(int initialV, int numEdges) {
        V = initialV;
        EL = new Edge[2 * numEdges]; // 2 * to account for back edges
        ELSize = 0;
        AL = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            AL.add(new ArrayList<>());
        }
    }

    void addEdge(int u, int v, long w, boolean directed) {
        if (u == v) return;                     // safeguard: no self loop
        EL[ELSize] = new Edge(v, w, 0);         // u->v, cap w, flow 0
        ELSize++;
        AL.get(u).add(ELSize - 1);              // remember this index
        EL[ELSize] = new Edge(u, directed ? 0 : w, 0);         // back edge
        ELSize++;
        AL.get(v).add(ELSize - 1);           // remember this index
    }

    long edmondsKarp(int s, int t) {
        long mf = 0;                            // mf stands for max_flow
        while (BFS(s, t)) {                     // an O(V*E^2) algorithm
            long f = sendOneFlow(s, t, INF);         // find and send 1 flow f
            if (f == 0) break;                  // if f == 0, stop
            mf += f;                            // if f > 0, add to mf
        }
        return mf;
    }

    long dinic(int s, int t) {
        long mf = 0;                            // mf stands for max_flow
        while (BFS(s, t)) {                     // an O(V^2*E) algorithm
            last = new int[V];                  // important speedup
            long f;
            while ((f = DFS(s, t, INF)) > 0) {   // exhaust blocking flow
                mf += f;
            }
        }
        return mf;
    }

    boolean BFS(int s, int t) {                 // find augmenting path
        d = new int[V];
        p = new Pair[V];                        // record BFS sp tree
        for (int i = 0; i < V; i++) {
            d[i] = -1;
            p[i] = new Pair(-1, -1);
        }
        d[s] = 0;
        Queue<Integer> q = new LinkedList<>();
        q.offer(s);
        while (!q.isEmpty()) {
            int u = q.poll();
            if (u == t) break;                  // stop as sink t reached
            for (int idx : AL.get(u)) {         // explore neighbors of u
                Edge e = EL[idx];               // stored in EL[idx]
                int v = e.v;
                long cap = e.w;
                long flow = e.f;
                if ((cap - flow > 0) && (d[v] == -1)) { // positive residual edge
                    d[v] = d[u] + 1;
                    q.offer(v);
                    p[v] = new Pair(u, idx);
                }
            }
        }
        return d[t] != -1;
    }

    // Run after performing Dinics/Edmonds Karp to get nodes in min-cut
    // Basically performs BFS on the flow graph one more time
    List<Integer> minCut(int s, int t) {
        List<Integer> result = new ArrayList<>();
        d = new int[V];
        p = new Pair[V];                        // record BFS sp tree
        for (int i = 0; i < V; i++) {
            d[i] = -1;
            p[i] = new Pair(-1, -1);
        }
        d[s] = 0;
        Queue<Integer> q = new LinkedList<>();
        q.offer(s);
        result.add(s);
        while (!q.isEmpty()) {
            int u = q.poll();
            if (u == t) break;                  // stop as sink t reached
            for (int idx : AL.get(u)) {         // explore neighbors of u
                Edge e = EL[idx];               // stored in EL[idx]
                int v = e.v;
                long cap = e.w;
                long flow = e.f;
                if ((cap - flow > 0) && (d[v] == -1)) { // positive residual edge
                    d[v] = d[u] + 1;
                    q.offer(v);
                    p[v] = new Pair(u, idx);
                    result.add(v);
                }
            }
        }
        return result;
    }

    long sendOneFlow(int s, int t, long f) {    // send one flow from s->t
        if (s == t) return f;                   // bottleneck edge f found
        Pair pair = p[t];
        int u = pair.first;
        int idx = pair.second;
        Edge e = EL[idx];
        long cap = e.w;
        long flow = e.f;
        long pushed = sendOneFlow(s, u, Math.min(f, cap - flow));
        e.f += pushed;
        EL[idx ^ 1].f -= pushed;            // back flow
        return pushed;
    }

    long DFS(int u, int t, long f) {            // traverse from s->t
        if ((u == t) || (f == 0)) return f;
        int start = last[u];
        int stop = AL.get(u).size();
        for (int i = start; i < stop; i++) {    // from last edge
            Edge e = EL[AL.get(u).get(i)];
            int v = e.v;
            long cap = e.w;
            long flow = e.f;
            if (d[v] != d[u] + 1) continue; // not part of layer graph
            long pushed;
            if ((pushed = DFS(v, t, Math.min(f, cap - flow))) > 0) {
                e.f += pushed;
                EL[AL.get(u).get(i) ^ 1].f -= pushed;    // back flow
                return pushed;
            }
        }
        return 0;
    }
}

