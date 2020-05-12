import math

def DEG_to_RAD(d): return d*math.pi/180.0

def RAD_to_DEG(r): return r*180.0/math.pi

class point:
    def __init__(self, _x, _y):                   # int or double
        self.x = _x
        self.y = _y
    def getX(self):
        return self.x
    def getY(self):
        return self.y

# returns 0/1/2 for inside/border/outside, respectively
def insideCircle(p, c, r):                        # all integer version
    dx = p.getX()-c.getX()
    dy = p.getY()-c.getY()
    Euc = dx*dx + dy*dy
    rSq = r*r
    return 1 if Euc < rSq else (0 if Euc == rSq else -1)

def circle2PtsRad(p1, p2, r, c_list):
    # to get the other center, reverse p1 and p2
    d2 = (p1.getX()-p2.getX()) * (p1.getX()-p2.getX()) + (p1.getY()-p2.getY()) * (p1.getY()-p2.getY())
    det = r*r / d2 - 0.25
    if det < 0.0: return False
    h = math.sqrt(det)
    c_list[0].x = (p1.getX()+p2.getX()) * 0.5 + (p1.getY()-p2.getY()) * h
    c_list[0].y = (p1.getY()+p2.getY()) * 0.5 + (p2.getX()-p1.getX()) * h
    return True

def main():
    # circle equation, inside, border, outside
    pt = point(2, 2)
    r = 7
    inside = point(8, 2)
    print(insideCircle(inside, pt, r))            # 1, inside
    border = point (9, 2)
    print(insideCircle(border, pt, r))            # 0, at border
    outside = point(10, 2)
    print(insideCircle(outside, pt, r))           # -1, outside

    d = 2*r
    print("Diameter = ", "{:.2f}".format(d))
    c = math.pi*d
    print("Circumference (Perimeter) = ", "{:.2f}".format(c))
    A = math.pi*r*r
    print("Area of circle = ", "{:.2f}".format(A))

    print("Length of arc   (central angle = 60 degrees) = ", "{:.2f}".format(60.0/360.0 * c))
    print("Length of chord (central angle = 60 degrees) = ", "{:.2f}".format(math.sqrt((2*r*r) * (1 - math.cos(DEG_to_RAD(60.0))))))
    print("Area of sector  (central angle = 60 degrees) = ", "{:.2f}".format(60.0/360.0 * A))

    p1 = point(0, 0)
    p2 = point(0.0, -1.0)
    ans = [point(0, 0)]                           # use a wrapper
    circle2PtsRad(p1, p2, 2.0, ans) 
    print("One of the center is (", "{:.2f}".format(ans[0].getX()), ",", "{:.2f}".format(ans[0].getY()), ")")
    circle2PtsRad(p2, p1, 2.0, ans)               # reverse p1 with p2
    print("The other center is (", "{:.2f}".format(ans[0].getX()), ",", "{:.2f}".format(ans[0].getY()), ")")

main()
