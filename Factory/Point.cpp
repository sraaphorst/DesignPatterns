#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;

// We want to create cartesian and polar points.
enum class PointType {
    cartesian,
    polar
};

class Point {
private:
    float x, y;

public:
    /**
     * Initialize from cartesian coordinates.
     */
    Point(float x, float y) : x{x}, y{y} {}

    /**
     * Now suppose we also want to be able to initialize from polar coordinates.
     * We could include polar coordinate initializer in Point directly.
     */
    // Not permitted since the arguments have the same type as the original Point constructor!
    //Point(float rho, float theta) {...}

    /**
     * SOLUTION 1:
     * Now instead, using PointType, we can generalize both constructors into one, but the names then become silly
     * as a and b provide no indication as to what they mean. Does a correspond to rho or theta?
     * Constructor is insufficient for describing arguments.
     */
     //! \param a this is either x or rho
     //! \param b this is either y or theta
     //! \param type
    Point(float a, float b, PointType type = PointType::cartesian) {
        switch (type) {
            case PointType::cartesian:
                x = a;
                y = b;
                break;

            case PointType::polar:
                x = a * cos(b);
                y = a * sin(b);
                break;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << '('<< point.x << ',' << point.y << ')';
        return os;
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y, PointType::cartesian};
    }
};

int main() {
    // Point constructor is private: must use factory methods.
    Point p1 {1, M_PI_2, PointType::polar};
    Point p2 {2, 0, PointType::cartesian};
    cout << p1 << " + " << p2 << " = " << (p1 + p2) << endl;
}