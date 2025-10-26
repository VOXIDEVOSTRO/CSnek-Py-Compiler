# Complex Python test file

import math, sys

class Vector:
    def __init__(self, x=0.0, y=0.0):
        self.x = x
        self.y = y

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

    def magnitude(self):
        return (self.x**2 + self.y**2) ** 0.5

def main():
    v1 = Vector(3, 4)
    v2 = Vector(1, 2)
    v3 = v1 + v2
    print(f"Result: ({v3.x}, {v3.y}), |v3|={v3.magnitude()}")

if __name__ == "__main__":
    main()