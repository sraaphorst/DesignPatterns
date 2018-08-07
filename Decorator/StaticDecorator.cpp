#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include <type_traits>
#include <vector>

struct Shape {
    virtual std::string str() const = 0;

    friend std::ostream &operator<<(std::ostream &out, const Shape &s);

    static std::string toString(double v) {
        double intpart;
        if (std::modf(v, &intpart) == 0.0)
            return std::to_string(static_cast<int>(v));
        else
            return std::to_string(v);
    }
};

std::ostream &operator<<(std::ostream &out, const Shape &s) {
    return out << s.str();
}

struct Circle : Shape {
    Circle(double radius) : radius(radius) {}

    std::string str() const override {
        return "Circle(" + toString(radius) + ')';
    }
private:
    double radius;
};

struct Square : Shape {
    Square(double side) : side(side) {}

    std::string str() const override {

        return "Square(" + toString(side) + ')';
    }

private:
    double side;
};

/// Instead of aggregating, we inherit from the template argument.
template<typename T>
struct ColouredShape : T {
    static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a shape.");

    std::string colour;

    ColouredShape() {}

    /// T is always going to be a shape so we can override.
    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has the colour " << colour;
    }
};

int main() {
    /// We want to be able to do things like:
    /// TransparentShape<ColouredShape<Square>> square{10, "red", 44};
}