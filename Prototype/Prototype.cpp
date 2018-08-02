/**
 * Prototypes: when it's easier to copy an existing object than create a new one.
 *
 * Complicated objects (e.g. cars) are not designed from scratch.
 * Idea: reiterate existing designs.
 *
 * A PROTOTYPE is a partially or fully constructed existing object.
 * Now you want to make variations of it, by making copies of the type and customizing it.
 * (Need deep copying.)
 *
 * Cloning of existing objects must be convenient (e.g. by factories).
 */

#include <common.h>
#include <ostream>

struct Address {
    Address(const string &street, const string &city, int suite) : street(street), city(city), suite(suite) {}

    Address(const Address &address) : street{address.street}, city{address.city}, suite{address.suite} {}

    string street;
    string city;
    int suite;

    friend ostream &operator<<(ostream &os, const Address &address) {
        os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite;
        return os;
    }
};

struct Contact {
    // Who deletes this pointer? Who owns it?
    Contact(const string &name, Address *address) : name{name}, address{address} {}

    // Deep copy constructor
    Contact(const Contact &other)
            : name{other.name},
              address{new Address{*other.address}} {}

    ~Contact() {
        delete address;
    }

    string name;

    // In the real world, people might keep a pointer in here for this instead of using by value, in which case
    // things end up much more complicated, as changes can propagate to many objects.
    // We need a deep copy.
    Address *address;

    friend ostream &operator<<(ostream &os, const Contact &contact) {
        os << "name: " << contact.name << " address: " << *contact.address;
        return os;
    }
};

int main() {
    // Lots of contacts... is it really worth replicating again and again, since address will be nearly the same?
    // By implementing a deep copy, we have introduced a simplistic type of Protoype design.
    Contact john{"John Doe", new Address{"123 East Drive", "London", 123}};

    // Now we do a deep copy, so Jane's address is not the same as John's.
    Contact jane = john;
    jane.name = "Jane Smith";
    jane.address->suite = 103;

    cout << john << endl << jane << endl;

}