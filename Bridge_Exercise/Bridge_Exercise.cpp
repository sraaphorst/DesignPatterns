#include <string>
using namespace std;

struct Shape;

struct Renderer {
    virtual string render(const Shape &t) const = 0;
};

struct Shape
{
    Shape(const Renderer &renderer, const string name) : renderer(renderer), name{std::move(name)} {}

    const Renderer &renderer;
    string name;

    string str() const {
        return renderer.render(*this);
    }
};

struct Triangle : Shape
{
    explicit Triangle(const Renderer &renderer) : Shape{renderer, "Triangle"} {}
};

struct Square : Shape
{
    explicit Square(const Renderer &renderer): Shape{renderer, "Square"} {}
};

struct RasterRenderer : Renderer {
    string render(const Shape &s) const override {
        return "Drawing " + s.name + " as pixels";
    }
};

struct VectorRenderer : Renderer {
    string render(const Shape &s) const override {
        return "Drawing " + s.name + " as lines";
    }
};