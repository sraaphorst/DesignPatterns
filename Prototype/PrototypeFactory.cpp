#include <common.h>

/**
 * Our previous implementation of using John as a prototype is not particularly convenient to users of our API.
 * So how do we give them a prototype of anything?
 */
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

/**
 * IDEA 1: GLOBAL VARIABLE.
 * People can just copy this, but it is hardly ideal.
 */
Contact prototype{"", new Address{"123 Main Road", "London", 0}};

/**
 * IDEA 2: Prototype factory.
 * Constructors for Contact and Address are private: have to go through factory.
 * Safe: stick prototypes in factory and get people to use factory.
 */
struct EmployeeFactory {
    static unique_ptr<Contact> newMainOfficeEmployee(const string &name, const int suite) {
        // This is our prototype
        static Contact prototype{"", new Address{"123 Main Road", "London", 0}};
        return newEmployee(name, suite, prototype);
    }

    static unique_ptr<Contact> newAuxiliaryOfficeEmployee(const string &name, const int suite) {
        // This is our prototype
        static Contact prototype{"", new Address{"321 Auxiliary Ave", "Sheffield", 0}};
        return newEmployee(name, suite, prototype);
    }

private:
    static unique_ptr<Contact> newEmployee(const string &name, const int suite, const Contact &prototype) {
        auto result = make_unique<Contact>(prototype);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

int main() {
    auto john = EmployeeFactory::newMainOfficeEmployee("John Smith", 123);
    auto jane = EmployeeFactory::newAuxiliaryOfficeEmployee("Jane Derp", 401);
    cout << *john << endl << *jane << endl;
}