class UFDS:
    def __init__(self, n):
        self.parents = list(range(n))
        self.ranks = [0] * n
        self.sizes = [1] * n
        self.numdisjoint = n

    def find(self, x):
        xp = x
        children = []
        while xp != self.parents[xp]:
            children.append(xp)
            xp = self.parents[xp]
        for c in children:
            self.parents[c] = xp
        return xp

    def union(self, a, b):
        ap = self.find(a)
        bp = self.find(b)
        if ap == bp:
            return

        if self.ranks[ap] < self.ranks[bp]:
            self.parents[ap] = bp
            self.sizes[bp] += self.sizes[ap]
        elif self.ranks[bp] < self.ranks[ap]:
            self.parents[bp] = ap
            self.sizes[ap] += self.sizes[bp]
        else:
            self.parents[bp] = ap
            self.ranks[ap] += 1
            self.sizes[ap] += self.sizes[bp]

        self.numdisjoint -= 1

    def size(self, x):
        return self.sizes[self.find(x)]


u = UFDS(8)
print(u.numdisjoint == 8)
u.union(1, 2)
print(u.find(1) == u.find(2))
print(u.find(1) != u.find(3))
print(u.find(2) != u.find(3))
print(u.size(1) == 2)
print(u.size(2) == 2)
print(u.size(3) == 1)
print(u.numdisjoint == 7)
u.union(1, 3)
print(u.find(1) == u.find(2))
print(u.find(1) == u.find(3))
print(u.find(2) == u.find(3))
print(u.find(2) != u.find(4))
print(u.size(1) == 3)
print(u.size(2) == 3)
print(u.size(3) == 3)
print(u.numdisjoint == 6)
u.union(2, 4)
print(u.find(1) == u.find(3))
print(u.find(2) == u.find(4))
print(u.size(1) == 4)
print(u.size(2) == 4)
print(u.numdisjoint == 5)
u.union(2, 3)
print(u.size(1) == 4)
print(u.size(2) == 4)
print(u.numdisjoint == 5)

# Example for https://open.kattis.com/problems/unionfind
# from sys import stdin, stdout
#
# def main():
#     n, q = [int(i) for i in stdin.readline().split(' ')]
#     u = UFDS(n)
#     for l in stdin.read()[:-1].split('\n'):
#         c, a, b = l.split(' ')
#         if c == '?':
#             stdout.write("yes\n" if u.find(int(a)) == u.find(int(b)) else "no\n")
#         else:
#             u.union(int(a), int(b))
#
# main()
