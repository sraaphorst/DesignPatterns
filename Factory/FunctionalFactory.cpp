#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
using namespace std;

#include "HotDrink.h"

/**
 * Similar to AbstractFactory, but instead of having to create complete factories as classes / structs with full
 * implementations, we can simply create a lambda expression to do the work.
 */
class DrinkWithVolumeFactory {
    map<string, function<unique_ptr<HotDrink>()>> factories;
public:
    DrinkWithVolumeFactory() {
        // Initialize the factories by providing the lambdas in-place.
        factories["tea"] = [] {
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };

        factories["coffee"] = [] {
            auto coffee = make_unique<Coffee>();
            coffee->prepare(50);
            return coffee;
        };
    }

    unique_ptr<HotDrink> makeDrink(const string &name) {
        return factories[name]();
    }
};

int main() {
   DrinkWithVolumeFactory factory;
   auto coffee = factory.makeDrink("coffee");
   auto tea    = factory.makeDrink("tea");
}