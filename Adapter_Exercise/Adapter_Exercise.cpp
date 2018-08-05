#include <iostream>
#include <memory>

struct Square
{
    int side{ 0 };


    explicit Square(const int side)
            : side(side)
    {
    }
};

struct Rectangle
{
    virtual int width() const = 0;
    virtual int height() const = 0;

    int area() const
    {
        return width() * height();
    }
};

struct SquareToRectangleAdapter : Rectangle
{
    SquareToRectangleAdapter(const Square& square) : side{square.side} {}

    int width() const override { return side; }
    int height() const override { return side; }
private:
    const int side;
};

int main() {
    std::unique_ptr<Rectangle> r = std::make_unique<SquareToRectangleAdapter>(Square{5});
    std::cout << "Area = " << r->area();
}