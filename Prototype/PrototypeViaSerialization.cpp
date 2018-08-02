#include <common.h>

/**
 * Instead of writing special code to traverse and deep copy an object, instead we use serialization / deserialization.
 * The issue is pointers, of course.
 */

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace boost;


struct Address {
    Address() {}

    Address(const string &street, const string &city, int suite) : street(street), city(city), suite(suite) {}

    Address(const Address &address) : street{address.street}, city{address.city}, suite{address.suite} {}

    string street;
    string city;
    int suite;

    friend ostream &operator<<(ostream &os, const Address &address) {
        os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite;
        return os;
    }

private:
    friend class serialization::access;

    template <class archive>
    void serialize(archive &ar, const unsigned version) {
        ar & street;
        ar & city;
        ar & suite;
    }
};

struct Contact {
    Contact() {}

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

private:
    friend class serialization::access;

    template <class archive>
    void serialize(archive &ar, const unsigned version) {
        ar & name;
        ar & address; // NOTE: we don't have to dereference.
    }
};


int main() {
    auto clone = [](const Contact &c) {
        // Serialize.
        ostringstream oss;
        archive::text_oarchive oa(oss);
        oa << c;
        string s = oss.str();
        cout << s << endl;

        // Now deserialize.
        istringstream iss{oss.str()};
        archive::text_iarchive ia(iss);
        Contact result;
        ia >> result;
        return result;
    };

    auto john = Contact{"John Smith", new Address{"123 Main Rd", "London", 123}};
    cout << john << endl;

    auto jane = clone(john);
    jane.name = "Jane Derp";
    jane.address->suite = 104;
    cout << jane << endl;
}