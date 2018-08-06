#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

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


/*** DECORATOR FOR COLOURED SHAPES ***/
struct ColouredShape : Shape {
    std::shared_ptr<Shape> shape;
    std::string colour;

    ColouredShape(const std::string &colour, const std::shared_ptr<Shape> shape) : shape(shape), colour(colour) {
        if (!colour.empty())
            this->colour[0] = toupper(this->colour[0]);
    }

    std::string str() const override {
        return colour + shape->str();
    }
};


int main() {
    Circle c{1};
    std::cout << c << std::endl;

    ColouredShape cs{"red", std::make_shared<Square>(4)};
    std::cout << cs << std::endl;
}