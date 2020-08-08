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

    def query(self, i, j):
        if i > 1:
            return self.query(1, j) - self.query(1, i - 1)

        s = 0
        while j > 0:
            s += self.ft[j]
            j -= self.lsone(j)

        return s

    def update(self, i, v):
        while i <= self.n:
            self.ft[i] += v
            i += self.lsone(i)

    def select(self, k):
        p = 1
        while (p * 2) <= self.n: p *= 2

        i = 0
        while p > 0:
            if k > self.ft[i + p]:
                k -= self.ft[i + p]
                i += p
            p //= 2

        return i + 1

class RUPQ:
    def __init__(self, n):
        self.ftree = FTree([0] * n)

    def query(self, i):
        return self.ftree.query(1, i)

    def update(self, i, j, v):
        self.ftree.update(i, v)
        self.ftree.update(j + 1, -v)

class RURQ:
    def __init__(self, n):
        self.f = FTree([0] * n)
        self.r = RUPQ(n)

    def query(self, i, j):
        if i > 1:
            return self.query(1, j) - self.query(1, i - 1)
        return self.r.query(j) * j - self.f.query(1, j)

    def update(self, i, j, v):
        self.r.update(i, j, v)
        self.f.update(i, v * (i - 1))
        self.f.update(j + 1, -1 * v * j)


f = [0, 1, 0, 1, 2, 3, 2, 1, 1, 0]
ft = FTree(f)
print(ft.query(1, 6) == 7)
print(ft.query(1, 3) == 1)
print(ft.select(7) == 6)
ft.update(5, 1)
print(ft.query(1, 10) == 12)

r = RUPQ(10)
r.update(2, 9, 7)
r.update(6, 7, 3)
print(r.query(1) == 0)
print(r.query(2) == 7)
print(r.query(3) == 7)
print(r.query(4) == 7)
print(r.query(5) == 7)
print(r.query(6) == 10)
print(r.query(7) == 10)
print(r.query(8) == 7)
print(r.query(9) == 7)
print(r.query(10) == 0)

r = RURQ(10)
r.update(2, 9, 7)
r.update(6, 7, 3)
print(r.query(3, 5) == 21)
print(r.query(7, 8) == 17)

# Example for https://open.kattis.com/problems/fenwick
# from sys import stdin, stdout
#
# def main():
#     n, q = [int(i) for i in stdin.readline().split(' ')]
#     f = FTree([0] * n)
#     for l in stdin.read()[:-1].split('\n'):
#         a = l.split(' ')
#         if a[0] == '?':
#             if a[1] == '0':
#                 stdout.write("0\n")
#             else:
#                 stdout.write("{}\n".format(f.q(1, int(a[1]))))
#         else:
#             f.u(int(a[1]) + 1, int(a[2]))
#
# main()
