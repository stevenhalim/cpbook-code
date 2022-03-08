import java.io.*;
import java.util.*;

class Pair {
    long flow, cost;

    Pair(long flow, long cost) {
        this.flow = flow;
        this.cost = cost;
    }

    @Override
    public String toString() {
        return flow + " " + cost;
    }
}

// Partially adapted from https://github.com/lewin/Algorithms/blob/master/src/Graph/Algorithms/NetworkFlow/Dinic.java
// Contains additional functions from https://github.com/stevenhalim/cpbook-code/blob/master/ch8/maxflow.cpp
class MinCostMaxFlow {
    static long INF = (long) 1e18; // INF = 1e18, not 2^63-1 to avoid overflow

    int numVertices, numEdges;
    int edgeIndex;
    int[] adjNodes, prevEdges, lastEdges, last;
    long[] flows, caps, costs, d;
    long totalCost;
    boolean[] vis;

    MinCostMaxFlow(int numVertices, int numEdges) {
        this.numVertices = numVertices;
        numEdges *= 2; // * 2 to account for back edges
        this.numEdges = numEdges;
        this.adjNodes = new int[numEdges];
        this.prevEdges = new int[numEdges];
        this.lastEdges = new int[numVertices];
        this.flows = new long[numEdges]; 
        this.caps = new long[numEdges];
        this.costs = new long[numEdges];
        this.edgeIndex = 0;
        this.last = new int[numVertices];
        this.vis = new boolean[numVertices];
        Arrays.fill(lastEdges, -1);
    }

    void addEdge(int u, int v, long w, long c, boolean directed) {
        if (u == v) return;                     // safeguard: no self loop

        adjNodes[edgeIndex] = v; caps[edgeIndex] = w; costs[edgeIndex] = c; flows[edgeIndex] = 0; // u->v, cap w, cost c, flow 0
        prevEdges[edgeIndex] = lastEdges[u]; lastEdges[u] = edgeIndex++;

        adjNodes[edgeIndex] = u; caps[edgeIndex] = directed ? 0 : w; costs[edgeIndex] = -c; flows[edgeIndex] = 0; // back edge
        prevEdges[edgeIndex] = lastEdges[v]; lastEdges[v] = edgeIndex++;
    }

    Pair mcmf(int s, int t) {
        long mf = 0;                            // mf stands for max_flow

        while (SPFA(s, t)) {                     // an O(V^2*E) algorithm
            System.arraycopy(lastEdges, 0, last, 0, numVertices);                  // important speedup
            long f;
            while ((f = DFS(s, t, INF)) > 0) {   // exhaust blocking flow
                mf += f;
            }
        }

        return new Pair(mf, totalCost);
    }

    boolean SPFA(int s, int t) { // SPFA to find augmenting path in residual graph
        d = new long[numVertices];
        Arrays.fill(d, INF);

        d[s] = 0;
        vis[s] = true;
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(s);

        while (!queue.isEmpty()) {
            int u = queue.poll();
            vis[u] = false;

            for (int idx = lastEdges[u]; idx != -1; idx = prevEdges[idx]) { // explore neighbors of u
                int v = adjNodes[idx];         // stored in adjNodes[idx]

                if (caps[idx] - flows[idx] > 0 && d[v] > d[u] + costs[idx]) { // positive residual edge
                    d[v] = d[u] + costs[idx];
                    if (!vis[v]) {
                        queue.offer(v);
                        vis[v] = true;
                    }
                }
            }
        }

        return d[t] != INF;                 // has an augmenting path
    }
    
    long DFS(int u, int t, long f) {            // traverse from u->t
        if ((u == t) || (f == 0)) return f;

        vis[u] = true;

        for (int idx = last[u]; idx != -1; last[u] = idx = prevEdges[idx]) {    // from last edge
            int v = adjNodes[idx];
            long cap = caps[idx];
            long flow = flows[idx];
            long cost = costs[idx];

            if (!vis[v] && d[v] == d[u] + cost) {       // in current layer graph
                long pushed;

                if ((pushed = DFS(v, t, Math.min(f, cap - flow))) > 0) {
                    totalCost += pushed * cost;
                    flows[idx] += pushed;
                    flows[idx ^ 1] -= pushed;           // back edge
                    vis[u] = false;
                    return pushed;
                }
            }
        }

        vis[u] = false;
        return 0;
    }
}

