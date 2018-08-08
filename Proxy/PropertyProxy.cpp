/**
 * A property is nothing more than a field with a getter and a setter.
 */

#include <iostream>

// We hack a simple template class to demonstrate, since C++ doss not have metaclasses.
// Metaclass: a class whose instances are classes.

// Suppose you want to intercept access to fields in Creature.
// You don't want to use getters and setters, though.
struct PlainCreature {
    int strength{10};
    int agility{10};
};

// Hence, we use properties
template <typename T>
struct Property {
    T value;

    Property(T value) {
        // We have overridden = and this is how we want to access the property anyway,
        // so we can do this.
        *this = value;
    }

    // You want to be able to treat this as of type T.
    operator T() {
        return value;
    }

    T operator=(T new_value) {
        return value = new_value;
    }
};

struct PropertyCreature {
    // If we don't have a constructor here, since Property does not have default constructors, this constructor
    // end sup being deleted.
    PropertyCreature(int strength, int agility) : strength{strength}, agility{agility} {}
    Property<int> strength;
    Property<int> agility;
};

int main() {
    PlainCreature c;
    c.strength = 15;

    PropertyCreature pc{10, 10};
    pc.agility = 20;
    std::cout << "The creature has strength " << pc.strength << " and agility " << pc.agility << std::endl;
}
