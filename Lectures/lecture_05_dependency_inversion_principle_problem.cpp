#include "common.h"

/**
 * DEPENDENCY INVERSION PRINCIPLE
 *
 * Specifies the best way to form dependencies between modules.
 *
 * A. High-level modules should not depend on low-level modules.
 *    Both should depend on abstractions.
 *
 * B. Abstractions should not depend on details.
 *    Details should depend on abstractions.
 *
 * Absractions are interfaces or base classes, and not concrete types.
 * The goal is to avoid depending on the implementation details (e.g. if you work with a library, you shouldn't have
 * to know that the implementation details include a vector).
 */

/// Example: modeling relationships between different people.
enum class Relationship {
    parent,
    child,
    sibling,
};

struct Person {
    string name;
};

/**
 * This is just a LOW-LEVEL MODULE.
 * It provides data storage, but no real functionality.
 */
struct Relationships {
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(Person &parent, Person &child) {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }
};

/**
 * This is a HIGH-LEVEL MODULE.
 * It provides actual results / research on the low-level module.
 */
struct Research {
    /**
     * We need to pass the data to the constructor.
     * The worst thing to do, which breaks the dependency inversion principle is to take a direct dependency on a
     * low-level module. We are going to do this to show how much of a bad idea it is.
     *
     * If the Relationships structure changes, this all falls apart.
     */
    Research(Relationships &relationships) {
        // Already a bad idea: now we are dependent on the fact that Relationships uses a vector of a rigid structure.
        auto &relations = relationships.relations;

        // Now we start using fancy C++17 techniques to traverse the tuples, and the low-level details changing will
        // break everything.
        for (auto &&[first, rel, second] : relations) {
            if (first.name == "John" && rel == Relationship::parent) {
                cout << "John has a child named " << second.name << endl;
            }
        }
    }
};

int main() {
    Person parent{"John"};
    Person child1{"Chris"};
    Person child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research research{relationships};
}