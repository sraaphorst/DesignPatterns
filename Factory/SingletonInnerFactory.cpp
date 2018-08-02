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

    class PointFactory {
    public:
        Point newCartesian(float x, float y) const {
            return {x, y};
        }

        Point newPolar(float r, float theta) const {
            return {r * cos(theta), r * sin(theta)};
        }
    };

public:
    /**
     * You could either make factory public or make a get method.
     * This gives some control over lifetime of factory: make constructor private, and then expose it as a field.
     */
    static const PointFactory factory;

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << '('<< point.x << ',' << point.y << ')';
        return os;
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }
};

const Point::PointFactory Point::factory;

int main() {
    auto p1 = Point::factory.newPolar(1, M_PI_2);
    auto p2 = Point::factory.newCartesian(2, 0);
    cout << p1 << " + " << p2 << " = " << (p1 + p2) << endl;
}