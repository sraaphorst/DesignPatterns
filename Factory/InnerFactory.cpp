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
    /**
     * Inner class: has access to private members of outer class, of course.
     * This only does not violate the open - closed principle if you predict it is needed.
     * Question: how do you want to expose this code? Create instance of via static methods?
     * At least this guides users to know how to create points, unlike Factory.
     *
     * This could be made a singleton as well.
     */
    class PointFactory {
    public:
        static Point newCartesian(float x, float y) {
            return {x, y};
        }

        static Point newPolar(float r, float theta) {
            return {r * cos(theta), r * sin(theta)};
        }
    };

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << '('<< point.x << ',' << point.y << ')';
        return os;
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }
};

int main() {
    auto p1 = Point::PointFactory::newPolar(1, M_PI_2);
    auto p2 = Point::PointFactory::newCartesian(2, 0);
    cout << p1 << " + " << p2 << " = " << (p1 + p2) << endl;
}