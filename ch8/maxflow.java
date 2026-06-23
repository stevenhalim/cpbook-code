import java.io.*;
import java.util.*;

class Edge {
    int u, v;
    long f;

    Edge(int u, int v, long f) {
        this.u = u;
        this.v = v;
        this.f = f;
    }

    @Override
    public String toString() {
        return u + " " + v + " " + f;
    }
}

// Partially adapted from https://github.com/lewin/Algorithms/blob/master/src/Graph/Algorithms/NetworkFlow/Dinic.java
// Contains additional functions from https://github.com/stevenhalim/cpbook-code/blob/master/ch8/maxflow.cpp
class maxflow {
    static long INF = 1l << 62; // 4E18

    int numVertices, numEdges;
    int edgeIndex;
    int[] adjNodes, prevEdges, lastEdges, d, last, bfsVertices, bfsEdges;
    long[] flows, caps;

    maxflow(int numVertices, int numEdges) {
        this.numVertices = numVertices;
        numEdges *= 2; // * 2 to account for back edges
        this.numEdges = numEdges;
        this.adjNodes = new int[numEdges];
        this.prevEdges = new int[numEdges];
        this.lastEdges = new int[numVertices];
        this.flows = new long[numEdges]; 
        this.caps = new long[numEdges];
        this.edgeIndex = 0;
        this.last = new int[numVertices];
        Arrays.fill(lastEdges, -1);
    }

    void addEdge(int u, int v, long w, boolean directed) {
        if (u == v) return;                     // safeguard: no self loop

        adjNodes[edgeIndex] = v; caps[edgeIndex] = w; flows[edgeIndex] = 0; // u->v, cap w, flow 0
        prevEdges[edgeIndex] = lastEdges[u]; lastEdges[u] = edgeIndex++;

        adjNodes[edgeIndex] = u; caps[edgeIndex] = directed ? 0 : w; flows[edgeIndex] = 0; // back edge
        prevEdges[edgeIndex] = lastEdges[v]; lastEdges[v] = edgeIndex++;
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
            System.arraycopy(lastEdges, 0, last, 0, numVertices);                  // important speedup
            long f;
            while ((f = DFS(s, t, INF)) > 0) {   // exhaust blocking flow
                mf += f;
            }
        }
        return mf;
    }

    boolean BFS(int s, int t) {                 // find augmenting path
        d = new int[numVertices];
        bfsVertices = new int[numVertices];   // record BFS sp tree
        bfsEdges = new int[numVertices];
        for (int i = 0; i < numVertices; i++) {
            d[i] = -1;
            bfsVertices[i] = bfsEdges[i] = -1;
        }

        d[s] = 0;
        int[] queue = new int[numVertices];
        int front = 0, back = 0;
        queue[back++] = s;

        while (front < back) {
            int u = queue[front++];
            if (u == t) break;                  // stop as sink t reached

            for (int idx = lastEdges[u]; idx != -1; idx = prevEdges[idx]) { // explore neighbors of u
                int v = adjNodes[idx];         // stored in adjNodes[idx]

                if (d[v] == -1 & flows[idx] < caps[idx]) {
                    d[v] = d[u] + 1;
                    queue[back++] = v;
                    bfsVertices[v] = u;
                    bfsEdges[v] = idx;
                }
            }
        }

        return d[t] != -1;
    }

    long sendOneFlow(int s, int t, long f) {    // send one flow from s->t
        if (s == t) return f;                   // bottleneck edge f found

        int u = bfsVertices[t];
        int idx = bfsEdges[t];

        long pushed = sendOneFlow(s, u, Math.min(f, caps[idx] - flows[idx]));
        flows[idx] += pushed;
        flows[idx ^ 1] -= pushed;               // back flow
        return pushed;
    }

    long DFS(int u, int t, long f) {            // traverse from u->t
        if ((u == t) || (f == 0)) return f;

        for (int idx = last[u]; idx != -1; last[u] = idx = prevEdges[idx]) {    // from last edge
            int v = adjNodes[idx];
            if (d[v] != d[u] + 1) continue; // not part of layer graph

            long pushed = DFS(v, t, Math.min(f, caps[idx] - flows[idx]));

            if (pushed > 0) {
                flows[idx] += pushed;
                flows[idx ^ 1] -= pushed;               // back flow
                return pushed;
            }
        }

        return 0;
    }

    // Run after performing Dinics/Edmonds Karp to get
    // nodes in min cut
    List<Integer> minCut(int s, int t) {
        List<Integer> result = new ArrayList<>();
        d = new int[numVertices];
        bfsVertices = new int[numVertices];   // record BFS sp tree
        bfsEdges = new int[numVertices];
        for (int i = 0; i < numVertices; i++) {
            d[i] = -1;
            bfsVertices[i] = bfsEdges[i] = -1;
        }

        d[s] = 0;
        int[] queue = new int[numVertices];
        int front = 0, back = 0;
        queue[back++] = s;
        result.add(s);

        while (front < back) {
            int u = queue[front++];
            if (u == t) break;                  // stop as sink t reached

            for (int idx = lastEdges[u]; idx != -1; idx = prevEdges[idx]) { // explore neighbors of u
                int v = adjNodes[idx];          // stored in adjNodes[idx]

                if (d[v] == -1 & flows[idx] < caps[idx]) {
                    d[v] = d[u] + 1;
                    queue[back++] = v;
                    bfsVertices[v] = u;
                    bfsEdges[v] = idx;
                    result.add(v);
                }
            }
        }

        return result;
    }
    
    // Run after performing Dinics/Edmonds Karp to get
    // edges in flow graph
    List<Edge> getFlowGraphEdges() {
        List<Edge> result = new ArrayList<>();

        for (int i = 0; i < numEdges; i++) {
            if (flows[i] > 0) {
                result.add(new Edge(adjNodes[i ^ 1], adjNodes[i], flows[i]));
            }
        }

        return result;
    }
}

