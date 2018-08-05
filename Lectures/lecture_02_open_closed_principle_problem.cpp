#include "common.h"

/*** OPEN / CLOSED PRINCIPLE ***
 * Your systems should be open to extension (e.g. inheritance), but closed to modification.
 */

/**
 * Assume you have a website selling products, and you want to be able to filter those products.
 */

enum class Colour { red, green, blue, };
enum class Size { small, medium, large, };

struct Product {
    string name;
    Colour colour;
    Size size;
};

/**
 * Say you want filters by colour and by size.
 * This ends up largely being a copy-paste, and poor, because we have to go back into chunk of already tested code.
 * Introduces a binary incompatibility if code is already released.
 * Then say we need to filter again by size AND colour. Now we are up to 2^N functions for N criteria.
 */
struct ProductFilter {
    static vector<Product*> by_colour(vector<Product*> items, Colour colour) {
        vector<Product*> result;
        copy_if(items.cbegin(), items.cend(), back_inserter(result), [colour](Product *p) { return p->colour == colour; });
        return result;
    }

    static vector<Product*> by_size(vector<Product*> items, Size size) {
        vector<Product*> result;
        copy_if(items.cbegin(), items.cend(), back_inserter(result), [size](Product *p) { return p->size == size; });
        return result;
    }

    static vector<Product*> by_size_and_colour(vector<Product*> items, Size size, Colour colour) {
        vector<Product*> result;
        copy_if(items.cbegin(), items.cend(), back_inserter(result), [size, colour](Product *p)
            { return p->size == size && p->colour == colour; });
        return result;
    }
};

int main() {
    Product apple{"Apple", Colour::green, Size::small};
    Product tree{"Tree",   Colour::green, Size::large};
    Product house{"House", Colour::blue,  Size::large};
    vector<Product*> items {&apple, &tree, &house};

    auto green_things = ProductFilter::by_colour(items, Colour::green);
    for (auto &i : green_things)
        cout << i->name << endl;

    return 0;
}