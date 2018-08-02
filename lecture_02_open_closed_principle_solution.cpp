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

// Forward declarations
template <typename> struct AndSpecification;
template <typename> struct OrSpecification;

/** Checks whether a given item satisfies a specification. **/
template <typename T> struct Specification {
    virtual bool is_satisfied(const T* const item) const = 0;

    // Combine specifications
    AndSpecification<T> operator&&(const Specification<T> &other) {
        return AndSpecification(*this, other);
    }

    OrSpecification<T> operator||(const Specification<T> &other) {
        return OrSpecification(*this, other);
    }
};

/** Filters a list of items based on a specification. **/
template <typename T> struct Filter {
    virtual vector<T*> filter(const vector<T*> items,
                              const Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Product> {
    vector<Product*> filter(const vector<Product*> items,
                            const Specification<Product> &spec) override {
        vector<Product*> result;
        copy_if(items.cbegin(), items.cend(), back_inserter(result), [&spec](auto x){ return spec.is_satisfied(x); });
        return result;
    }
};

struct ColourSpecification : Specification<Product> {
    const Colour colour;

    ColourSpecification(Colour colour): colour(colour) {}

    bool is_satisfied(const Product * const item) const override {
        return item->colour == colour;
    }
};

struct SizeSpecification : Specification<Product> {
    const Size size;

    SizeSpecification(Size size) : size(size) {}

    bool is_satisfied(const Product * const item) const override {
        return item->size == size;
    }
};

template <typename T> struct AndSpecification : Specification<T> {
    const Specification<T> &s1;
    const Specification<T> &s2;

    AndSpecification(const Specification<T> &s1, const Specification<T> &s2): s1(s1), s2(s2) {}

    bool is_satisfied(const T* const t) const override {
        return s1.is_satisfied(t) && s2.is_satisfied(t);
    };
};

template <typename T> struct OrSpecification : Specification<T> {
    const Specification<T> &s1;
    const Specification<T> &s2;

    OrSpecification(const Specification<T> &s1, const Specification<T> &s2): s1(s1), s2(s2) {}

    bool is_satisfied(const T* const t) const override {
        return s1.is_satisfied(t) || s2.is_satisfied(t);
    };
};

int main() {
    Product apple{"Apple", Colour::green, Size::small};
    Product tree{"Tree",   Colour::green, Size::large};
    Product house{"House", Colour::blue,  Size::large};
    vector<Product*> items {&apple, &tree, &house};

    BetterFilter bf;
    auto spec = ColourSpecification{Colour::green} && SizeSpecification{Size::large};
    for (auto &i : bf.filter(items, spec))
        cout << i->name << " is green and large." << endl;

    return 0;
}