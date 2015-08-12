from math import sqrt

class Complex(object):
    def __init__(self, x, y):
        self.x,self.y = x,y
        
    def __str__(self):
        if self.x != 0 and self.y > 0:
            return "%0.2f + %0.2fi" % (self.x, abs(self.y))
        elif self.x != 0 and self.y < 0:
            return "%0.2f - %0.2fi" % (self.x, abs(self.y))
        elif self.x == 0 and self.y > 0:
            return "%0.2fi" % abs(self.y)
        elif self.x == 0 and self.y < 0:
            return "-%0.2fi" % abs(self.y)
        else:
            return "%0.2f" % self.x
        
    def __add__(self, other):
        return Complex(self.x+other.x, self.y+other.y)
    def __sub__(self, other):
        return Complex(self.x-other.x, self.y-other.y)
    def __mul__(self, other):
        return Complex(self.x*other.x-self.y*other.y, 
                       self.x*other.y+self.y*other.x)
    def numdiv(self, p):
        return Complex(self.x/p, self.y/p)
    def mod(self):
        return sqrt(self.x**2 + self.y**2)
    def __div__(self, other):
        sopr = Complex(other.x, -other.y)
        return (self * sopr).numdiv(other.mod()**2)

a = map(float,raw_input().split())
b = map(float,raw_input().split())
C = Complex(float(a[0]),float(a[1]))
D = Complex(float(b[0]),float(b[1]))

print C + D
print C - D
print C * D
print C / D
print "%0.2f" % C.mod()
print "%0.2f" % D.mod()
