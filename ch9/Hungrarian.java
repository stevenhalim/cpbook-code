import java.util.*;

/*
Adapted from: https://github.com/ShahjalalShohag/code-library/blob/master/Graph%20Theory/Hungarian%20Algorithm.cpp
Complexity: O(n^3) but optimized
It finds minimum cost maximum matching.
For finding maximum cost maximum matching
add -cost and return -matching()
1-indexed
*/
class Hungrarian {
    static int N = 2005;
    static long inf = (long) 1e18;

    long[][] c;
    long[] fx, fy, d;
    int[] l, r, arg, trace;
    Queue<Integer> q;
    int start, finish, n;

    Hungrarian() {
        c = new long[N][N];
        fx = new long[N];
        fy = new long[N];
        d = new long[N];
        l = new int[N];
        r = new int[N];
        arg = new int[N];
        trace = new int[N];
    }

    Hungrarian(int n1, int n2) {
        this();
        n = Math.max(n1, n2);

        for (int i = 1; i <= n; ++i) {
            fy[i] = l[i] = r[i] = 0;
            for (int j = 1; j <= n; ++j) c[i][j] = inf;
        }
    }

    void addEdge(int u, int v, long cost) {
        c[u][v] = Math.min(c[u][v], cost);
    }

    long getC(int u, int v) {
        return c[u][v] - fx[u] - fy[v];
    }

    void initBFS() {
        q = new LinkedList<>();
        q.offer(start);

        for (int i = 0; i <= n; ++i) trace[i] = 0;

        for (int v = 1; v <= n; ++v) {
            d[v] = getC(start, v);
            arg[v] = start;
        }

        finish = 0;
    }

    void findAugPath() {
        while (!q.isEmpty()) {
            int u = q.poll();

            for (int v = 1; v <= n; ++v) {
                if (trace[v] == 0) {
                    long w = getC(u, v);

                    if (w == 0) {
                        trace[v] = u;

                        if (r[v] == 0) {
                            finish = v;
                            return;
                        }

                        q.offer(r[v]);
                    }

                    if (d[v] > w) {
                        d[v] = w;
                        arg[v] = u;
                    }
                }
            }
        }
    }

    void subXAddY() {
        long delta = inf;

        for (int v = 1; v <= n; ++v) {
            if (trace[v] == 0 && d[v] < delta) {
                delta = d[v];
            }
        }

        // Rotate
        fx[start] += delta;

        for (int v = 1; v <= n; ++v) {
            if(trace[v] != 0) {
                int u = r[v];
                fy[v] -= delta;
                fx[u] += delta;
            } else {
                d[v] -= delta;
            }
        }

        for (int v = 1; v <= n; ++v) if (trace[v] == 0 && d[v] == 0) {
            trace[v] = arg[v];

            if (r[v] == 0) {
                finish = v;
                return;
            }

            q.offer(r[v]);
        }
    }

    void Enlarge() {
        do {
            int u = trace[finish];
            int nxt = l[u];
            l[u] = finish;
            r[finish] = u;
            finish = nxt;
        } while (finish != 0);
    }

    long maximumMatching() {
        for (int u = 1; u <= n; ++u) {
            fx[u] = c[u][1];
            for (int v = 1; v <= n; ++v) {
                fx[u] = Math.min(fx[u], c[u][v]);
            }
        }

        for (int v = 1; v <= n; ++v) {
            fy[v] = c[1][v] - fx[1];
            for (int u = 1; u <= n; ++u) {
                fy[v] = Math.min(fy[v], c[u][v] - fx[u]);
            }
        }

        for (int u = 1; u <= n; ++u) {
            start = u;
            initBFS();
            while (finish == 0) {
                findAugPath();
                if (finish == 0) subXAddY();
            }
            Enlarge();
        }

        long ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (c[i][l[i]] != inf) ans += c[i][l[i]];
            else l[i] = 0;
        }
        return ans;
    }
}
