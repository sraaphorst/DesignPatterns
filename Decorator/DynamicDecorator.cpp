#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

struct Shape {
    virtual std::string str() const = 0;
};

struct Circle : Shape {
    double radius;

    Circle() {}
    Circle(double radius) : radius(radius) {}

    void resize(double factor) {
        radius *= factor;
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << "Circle(" << radius << ")";
        return oss.str();
    }
};

struct Square : Shape {
    double side;

    Square() {}
    Square(double side) : side(side) {}

    std::string str() const override {
        std::ostringstream oss;
        oss << "Square(" << side << ")";
        return oss.str();
    }
};

/**
 * We want to add colour to these shapes while obeying the open-closed principle.
 */

struct ColouredShape : Shape {
    Shape &s;
    std::string colour;

    ColouredShape(Shape &s, const std::string &colour) : s{s}, colour{colour} {}

    std::string str() const override {
        std::string caps = colour;
        caps[0] = std::toupper(caps[0]);
        return caps + s.str();
    }
};

int main() {

}