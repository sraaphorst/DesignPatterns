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
 * Now, to avoid the low-level dependencies and to introduce an abstraction to help, we create a RelationshipBrowser.
 */
struct RelationshipBrowser {
    virtual vector<Person> findAllChildrenOf(const string &name) = 0;
};

/**
 * This is a LOW-LEVEL MODULE.
 * Now we allow it to provide some functionality, such as that of the relationship browser, so that its implementation
 * details do not affect high-level modules.
 */
struct Relationships : RelationshipBrowser {
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(Person &parent, Person &child) {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    // Relationships is now conformed to the RelationshipBrowser interface through this function.
    vector<Person> findAllChildrenOf(const string &name) override {
        vector<Person> result;
        for (auto &&[first, rel, second] : relations) {
            if (first.name == name && rel == Relationship::parent)
                result.push_back(second);
        }
        return result;
    }
};

/**
 * This is a HIGH-LEVEL MODULE.
 * It provides actual results / research on the low-level module.
 */
struct Research {
    /**
     * We need to pass the data to the constructor.
     * Now, however, we no longer need to know the structure of the low-level implementation to research, and can
     * instead assume we got a RelationshipBrowser
     */
    Research(RelationshipBrowser &browser) {
        for (const auto &p: browser.findAllChildrenOf("John"))
            cout << "John has a child called " << p.name << endl;
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