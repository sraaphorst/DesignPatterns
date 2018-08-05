#include <iostream>

/**
 * Example with shapes (say circle, square, etc.) and renderers for those shapes, say raster renderer (pixels)
 * and vector renderer (lines). This could give us a 2x2 class situation.
 */

struct Renderer {
    virtual void renderCircle(double x, double y, double radius) = 0;
};

struct VectorRenderer : Renderer {
    void renderCircle(double x, double y, double radius) override {
        std::cout << "Vector-rendering a circle of radius " << radius << std::endl;
    }
};

struct RasterRenderer : Renderer {
    void renderCircle(double x, double y, double radius) override {
        std::cout << "Raster-rendering a circle of radius " << radius << std::endl;
    }
};

struct Shape {
protected:
    /// Bridge to the renderer.
    Renderer &renderer;
    Shape(Renderer &renderer) : renderer(renderer) {}

public:
    virtual void draw() = 0;
    virtual void resize(double factor) = 0;
};

struct Circle : Shape {
    double x;
    double y;
    double radius;

    Circle(Renderer &renderer, double x, double y, double radius) : Shape{renderer}, x{x}, y{y}, radius{radius} {}

    void draw() override {
        /// Inherits reference to renderer.
        renderer.renderCircle(x, y, radius);
    }

    void resize(double factor) override {
        radius *= factor;
    }
};

int main() {
    RasterRenderer rr;
    Circle rasterCircle{rr, 5, 5, 5};
    rasterCircle.draw();
    rasterCircle.resize(2);
    rasterCircle.draw();
}