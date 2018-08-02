#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;

class Point {
private:
    float x, y;

    /**
     * Private constructor.
     */
    Point(float x, float y) : x{x}, y{y} {}

public:
    /// Cartesian factory method.
    static Point newCartesian(float x, float y) {
        return {x, y};
    }

    /// Polar factory method.
    static Point newPolar(float r, float theta) {
        return {r * cos(theta), r * sin(theta)};
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << '('<< point.x << ',' << point.y << ')';
        return os;
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }
};

int main() {
    auto p1 = Point::newPolar(1, M_PI_2);
    auto p2 = Point::newCartesian(2, 0);
    cout << p1 << " + " << p2 << " = " << (p1 + p2) << endl;
}