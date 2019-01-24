class FTree:
    def __init__(self, f):
        self.n = len(f)
        self.ft = [0] * (self.n + 1)

        for i in range(1, self.n + 1):
            self.ft[i] += f[i - 1]
            if i + self.lsone(i) <= self.n:
                self.ft[i + self.lsone(i)] += self.ft[i]

    def lsone(self, s):
        return s & (-s)

    def q(self, i, j):
        if i > 1:
            return self.q(1, j) - self.q(1, j - 1)

        s = 0
        while j > 0:
            s += self.ft[j]
            j -= self.lsone(j)

        return s

    def u(self, i, v):
        while i <= self.n:
            self.ft[i] += v
            i += self.lsone(i)

    def s(self, k):
        lo = 1
        hi = self.n

        for i in range(30):
            mid = (lo + hi) // 2
            if self.q(1, mid) < k:
                lo = mid
            else:
                hi = mid
        
        return hi

class RUPQ:
    def __init__(self, n):
        self.ftree = FTree([0] * n)

    def q(self, i):
        return self.ftree.q(1, i)

    def u(self, i, j, v):
        self.ftree.u(i, v)
        self.ftree.u(j + 1, -v)

class RURQ:
    def __init__(self, n):
        self.f = FTree([0] * n)
        self.r = RUPQ(n)

    def q(self, i, j):
        if i > 1:
            return self.q(1, j) - self.q(1, i - 1)
        return self.r.q(j) * j - self.f.q(1, j)

    def u(self, i, j, v):
        self.r.u(i, j, v)
        self.f.u(i, v * (i - 1))
        self.f.u(j + 1, -1 * v * j)


f = [0, 1, 0, 1, 2, 3, 2, 1, 1, 0]
ft = FTree(f)
print(ft.q(1, 6) == 7)
print(ft.q(1, 3) == 1)
print(ft.s(7) == 6)
ft.u(5, 1)
print(ft.q(1, 10) == 12)

r = RUPQ(10)
r.u(2, 9, 7)
r.u(6, 7, 3)
print(r.q(1) == 0)
print(r.q(2) == 7)
print(r.q(3) == 7)
print(r.q(4) == 7)
print(r.q(5) == 7)
print(r.q(6) == 10)
print(r.q(7) == 10)
print(r.q(8) == 7)
print(r.q(9) == 7)
print(r.q(10) == 0)

r = RURQ(10)
r.u(2, 9, 7)
r.u(6, 7, 3)
print(r.q(3, 5) == 21)
print(r.q(7, 8) == 17)
