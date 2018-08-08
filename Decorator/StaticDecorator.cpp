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

    void resize(double factor) {
        radius *= factor;
    }
private:
    double radius;
};

struct Square : Shape {
    Square(double side) : side(side) {}

    std::string str() const override {
        return "Square(" + toString(side) + ')';
    }

    void resize(double factor) {
        side *= factor;
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

    /*** STUDY THIS ***
     * We want to be able to do things like:
     * TransparentShape<ColouredShape<Square>> square{10, "red", 44};
     * This constructor picks off the colour argument, and forwards the rest of the arguments on.
     */
    template <typename...Args>
    ColouredShape(const std::string colour, Args ...args)
            : T(std::forward<Args>(args)...), colour{colour} {}

    /// T is always going to be a shape so we can override.
    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has the colour " << colour;
        return oss.str();
    }
};

/// Instead of aggregating, we inherit from the template argument.
template<typename T>
struct TransparentShape : T {
    static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a shape.");

    uint8_t transparency;

    template <typename...Args>
    TransparentShape(const uint8_t transparency, Args ...args)
            : T(std::forward<Args>(args)...), transparency{transparency} {}

    /// T is always going to be a shape, so we can override.
    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has "
            << static_cast<double>(transparency) / 255 * 100
            << "% transparency";
        return oss.str();
    }
};

int main() {
    /// NOTE: parameters must be ordered: first, transparency, then, colour, and finally, shape.
    TransparentShape<ColouredShape<Circle>> green_circle{200, "green", 1.5};
    green_circle.resize(10);
    std::cout << green_circle.str() << std::endl;
}