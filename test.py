import math, sys

class Vector:
    """Triple-quoted String AHH"""
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

    print(f"Result: ({v3.x}, {v3.y}), |v3|={v3.magnitude():.2f}")

    path = r"C:\Users\test\file.txt"

    data = b"\x41\x42\x43"

    regex = fr"\d+\s+\w+"

    big = 1_000_000
    sci = 6.022e23
    ratio = 22/7
    floor = 22//7

    if v1.x > v2.x and v1.y >= v2.y:
        print("v1 is bigger")
    elif v1.x != v2.x or v1.y <= v2.y:
        print("mixed comparison")
    else:
        print("equalish")

    try:
        with open("temp.txt", "w") as f:
            f.write("hello")
    except IOError as e:
        print("IO error", e)
    finally:
        print("done")

if __name__ == "__main__":
    main()