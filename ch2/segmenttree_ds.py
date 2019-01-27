class STree:
    def __init__(self, l):
        self.l = l
        self.n = len(l)
        self.st = [0] * (4 * self.n)
        self.islazy = [False] * (4 * self.n)
        self.lazy = [0] * (4 * self.n)

        self.build(1, 0, self.n - 1)

    def left(self, p):
        return p << 1

    def right(self, p):
        return (p << 1) + 1

    def build(self, p, l, r):
        if (l == r):
            self.st[p] = l
        else:
            self.build(self.left(p), l, (l + r) // 2)
            self.build(self.right(p), (l + r) // 2 + 1, r)
            p1 = self.st[self.left(p)]
            p2 = self.st[self.right(p)]
            if self.l[p1] <= self.l[p2]:
                self.st[p] = p1
            else:
                self.st[p] = p2

    def _q(self, p, pl, pr, fr, to):
        if fr > pr or to < pl:
            return -1, -1
        if self.islazy[p]:
            return fr, self.lazy[p]
        if fr <= pl and to >= pr:
            return self.st[p], self.l[self.st[p]]

        res1 = self._q(self.left(p), pl, (pl + pr) // 2, fr, to)
        res2 = self._q(self.right(p), (pl + pr) // 2 + 1, pr, fr, to)

        if (res1[0] == -1):
            return res2
        elif res2[0] == -1:
            return res1
        elif res1[1] <= res2[1]:
            return res1
        else:
            return res2

    def _u(self, p, pl, pr, fr, to, newval):
        if fr > pr or to < pl:
            return self.st[p]

        if fr == pl and to == pr:
            if fr == to:
                self.l[pl] = newval
                self.islazy[p] = False
            else:
                self.lazy[p] = newval
                self.islazy[p] = True

            self.st[p] = fr
            return self.st[p]

        pm = (pl + pr) // 2

        if self.islazy[p]:
            self.islazy[p] = False
            self.islazy[self.left(p)] = True
            self.islazy[self.right(p)] = True
            self.lazy[self.left(p)] = self.lazy[p]
            self.lazy[self.right(p)] = self.lazy[p]
            self.st[self.left(p)] = pl
            self.st[self.right(p)] = pm

        p1 = self._u(self.left(p), pl, pm, max(fr, pl), min(to, pm), newval)
        p2 = self._u(self.right(p), pm + 1, pr, max(fr, pm + 1), min(to, pr), newval)

        if self.l[p1] <= self.l[p2]:
            self.st[p] = p1
        else:
            self.st[p] = p2
        return self.st[p]

    def q(self, fr, to):
        return self._q(1, 0, self.n - 1, fr, to)[0]

    def u(self, fr, to, val):
        return self._u(1, 0, self.n - 1, fr, to, val)


l = [18, 17, 13, 19, 15, 11, 20]
st = STree(l)
print(st.q(0, 0) == 0)
print(st.q(1, 3) == 2)
print(st.q(4, 6) == 5)
st.u(5, 5, 99)
print(st.q(1, 3) == 2)
print(st.q(4, 6) == 4)
st.u(0, 3, 7)
print(st.q(1, 3) == 1)
print(st.q(3, 6) == 3)
st.u(3, 4, 5)
print(st.q(1, 3) == 3)
print(st.q(4, 6) == 4)
