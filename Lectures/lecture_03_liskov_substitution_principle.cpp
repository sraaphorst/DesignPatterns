/** LISKOV SUBSTITUTION PRINCIPLE:
#include "common.h"

class Rectangle {
protected:
    int width, height;

public:
    Rectangle(int width, int height) : width(width), height(height) {}

    int getWidth() const {
        return width;
    }

    virtual void setWidth(int width) {
        Rectangle::width = width;
    }

    int getHeight() const {
        return height;
    }

    virtual void setHeight(int height) {
        Rectangle::height = height;
    }

    int area() const {
        return width * height;
    }
};

/** Existing part of our API. **/
void process(Rectangle &r) {
    int w = r.getWidth();
    r.setHeight(10);

    cout << "expected area = " << (w*10)
         << ", got " << r.area() << endl;
}

/**
 * Now suppose somewhere down the line, you decide to inherit from rectangle to make a square.
 * You make setWidth and setHeight set both properties since they must be the same for squares.
 *
 * This, however, violates the Liskov substitution principle, because now we cannot use square with
 * our process function above.
 */
class Square : public Rectangle {
public:
    Square(int size) : Rectangle{size, size} {}

    void setWidth(int width) override {
        this->width = this->height = width;
    }

    void setHeight(int height) override {
        this->width = this->height = height;
    }
};

/**
 * Possible solutions:
 * 1. Have just rectangle, with a boolean check as to whether or not it's a square.
 * 2. Use a RectangleFactory:

struct RectangleFactory {
    static Rectangle createRectangle(int width, int height);
    static Rectangle createSquare(int size);
};
 */

int main() {
    Rectangle r{3, 4};
    process(r);

    Square s{5};
    process(s);
}