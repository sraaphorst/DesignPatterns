#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include <vector>

struct Flower
{
    virtual std::string str() = 0;
};

struct Rose : Flower
{
    std::string str() override {
        return "A rose";
    }
};

struct RedFlower : Flower {
    RedFlower(Flower &f): f{f} {}
    std::string str() override {
        auto fstr = f.str();
        if (fstr.find("red") != std::string::npos)
            return f.str();
        if (fstr.find("that is") == std::string::npos)
            return f.str() + " that is red";
        else
            return f.str() + " and red";
    }

    Flower &f;
};

struct BlueFlower : Flower {
    BlueFlower(Flower &f): f{f} {}
    std::string str() override {
        auto fstr = f.str();
        if (fstr.find("blue") != std::string::npos)
            return f.str();
        if (fstr.find("that is") == std::string::npos)
            return f.str() + " that is blue";
        else
            return f.str() + " and blue";
    }

    Flower &f;
};

int main() {
    Rose rose;
    RedFlower red_rose{rose};
    RedFlower red_red_rose{red_rose};
    BlueFlower blue_red_rose{red_rose};
    std::cout << rose.str(); // A rose
    std::cout << red_rose.str(); // A rose that is red
    std::cout << red_red_rose.str(); // A rose that is red
    std::cout << blue_red_rose.str(); // A rose that is blue and red
}