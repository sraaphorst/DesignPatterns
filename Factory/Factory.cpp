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
    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << '('<< point.x << ',' << point.y << ')';
        return os;
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }

    // Violation of the open-closed principle.
    friend struct PointFactory;
};

/**
 * The difference between a factory method and a factory is that the factory is in a separate class.
 * GoF does not have a Factory: only an AbstractFactory.
 * Many ways to expose the factory:
 * 1. Can create the factory.
 * 2. Can just invoke if the members are static.
 * Note that in this case, we violated the open-closed principle as the constructor of Point is private.
 *
 * PROBLEM: There is no obvious connection between Point and PointFactory from a user perspective.
 * To avoid this, people may put the factory inside the type.
 */
struct PointFactory {
    static Point newCartesian(float x, float y) {
        return {x, y};
    }

    static Point newPolar(float r, float theta) {
        return {r * cos(theta), r * sin(theta)};
    }
};

int main() {
    auto p1 = PointFactory::newPolar(1, M_PI_2);
    auto p2 = PointFactory::newCartesian(2, 0);
    cout << p1 << " + " << p2 << " = " << (p1 + p2) << endl;
}