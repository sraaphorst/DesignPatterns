#include <iostream>
#include <map>
#include <memory>
#include <string>
using namespace std;

#include "HotDrink.h"

 /**
  * Idea here: families of products (e.g. hot drinks in this example), and thus, a family of factories.
  * The family of factories use inheritance to polymorphically invoke the different factories.
  */

/**
 * This is the abstract factory and its family of factory implementations.
 */
struct HotDrinkFactory {
    virtual unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinkFactory {
    unique_ptr<HotDrink> make() const override {
        return make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory {
    unique_ptr<HotDrink> make() const override {
        return make_unique<Coffee>();
    }
};



/**
 * Factory that keeps track of what we have made and how to make it, on the basis of different factories.
 */
class DrinkFactory {
private:
    // We will fetch factory by drink name, and then it will be invoked polymorphically through call to make.
    // We can stick these into any data structure, however.
    map<string, unique_ptr<HotDrinkFactory>> hotFactories;

public:
    DrinkFactory() {
        hotFactories["coffee"] = make_unique<CoffeeFactory>();
        hotFactories["tea"]    = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> makeDrink(const string &drinkName) {
        auto drink = hotFactories[drinkName]->make();
        drink->prepare(200);
        return drink;
    }
};

/**
 * Without AbstractFactory, this is what we would have to do.
 */
unique_ptr<HotDrink> makeDrink(string type) {
    unique_ptr<HotDrink> drink;
    // If we didn't have an abstract factory, we would need to do something like:
    if (type == "tea") {
        drink = make_unique<Tea>();
        drink->prepare(200);
    } else {
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}

int main() {
    auto tea1 = makeDrink("tea");
    auto coffee1 = makeDrink("coffee");

    DrinkFactory factory;
    auto tea2 = factory.makeDrink("tea");
    auto coffee2 = factory.makeDrink("coffee");
}