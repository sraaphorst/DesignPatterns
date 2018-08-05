/**
 * In drawing apps, you can drag individual shapes, or you can select several different shapes and drag them together.
 */

#include <algorithm>
#include <cstdarg>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

struct IDGenerator {
    size_t count = 0;
    size_t gen() { return ++count; }
};

/**
 * This draw method is what allows us to use shapes and groups in a uniform manner, i.e. it handles the composite
 * nature of this.
 */
struct DrawableObject {
    virtual void draw() = 0;
};

struct Circle: DrawableObject {
    Circle(): id{gen.gen()} {};

    void draw() override {
        std::cout << "Circle" << id;
    }

private:
    const size_t id;
    static IDGenerator gen;
};

IDGenerator Circle::gen{};


struct Triangle: DrawableObject {
    Triangle(): id{gen.gen()} {};

    void draw() override {
        std::cout << "Triangle" << id;
    }

private:
    const size_t id;
    static IDGenerator gen;
};

IDGenerator Triangle::gen{};



struct Group: DrawableObject {
    std::string name;
    std::vector<DrawableObject*> objects;

    Group(std::string name, std::initializer_list<DrawableObject*> pobjects)
    : name{std::move(name)}, objects{pobjects} {}

    void draw() override {
        std::cout << name << "[";
        bool isFirst = true;
        std::for_each(std::begin(objects), std::end(objects), [&isFirst](auto &o){
            if (!isFirst) std::cout << ',';
            isFirst = false;
            o->draw();
        });
        std::cout << ']';
    }
};

int main() {
    Circle c1, c2;
    Triangle t1;
    Group circles{"CircleGroup", {&c1, &c2}};
    Group root{"RootGroup", {&circles, &t1}};
    root.draw();
}