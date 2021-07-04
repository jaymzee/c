#include <iostream>
#include <memory>

// Most classes should not directly handle resources, but instead use
// members that perform resource handling for them.
//  - for memory it can be unique_ptr, share_ptr, vector, etc.
//  - for files it can be ofstream, ifstream
// Classes that avoid handling resources don't need to define any of the
// special member functions required to properly handle resources
//
// Rule of Zero
//
// However for the base class of a polymorphic hierarchy, the destructor
// should be declared public and virtual. This blocks implicit moves (and
// deprecates implicit copies), and so the special member functions have
// to be defaulted, however this makes the class prone to slicing, which is
// why polymorphic classes often define copy as deleted.
// A polymorphic class should suppress copying, which leads to the following
// generic wording for the Rule of Five:
//
// If you define or =delete any default operation, define or =delete them all.
//
class Shape {
    int cx;
    int cy;
protected:
    virtual ~Shape() = default;
    virtual const char *name() const = 0;
public:
    Shape() : cx(0), cy(0) {}
    Shape(const Shape&) = delete;
    Shape& operator=(const Shape&) = delete;
    void move(int x, int y) {
        cx = x;
        cy = y;
    }
    friend std::ostream& operator<<(std::ostream& os, const Shape& s);
};

std::ostream& operator<<(std::ostream& os, const Shape& s)
{
    os << s.name() << " { x: " << s.cx << " y: " << s.cy << " }";
    return os;
}

class Circle: public Shape {
    int radius;
public:
    Circle(int radius) : radius(radius) {}
    const char *name() const { return "Circle"; }
};

class Rectangle: public Shape {
    int width;
    int height;
public:
    Rectangle(int width, int height) : width(width), height(height) {}
    const char *name() const { return "Rectangle"; }
};

int main(int argc, char *argv[])
{
    Circle c(5);
    Rectangle r(3,4);

    Shape &s = r;

    s.move(4, 5);
    std::cout << s << std::endl;

    return 0;
}

