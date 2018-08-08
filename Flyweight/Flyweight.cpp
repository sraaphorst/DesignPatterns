/// Example: MMORPG with lots of users with similar names.

/// Bimap allows us to search easily on both sides: key -> value, value -> key.
#include <boost/bimap.hpp>

#include <array>
#include <iostream>
#include <string>

/// First attempt:
struct User1 {
    std::string name;
};

/// Second attempt:
struct User2 {
    std::string first_name;
    std::string last_name;
};

/// Final attempt:
/// Instead, store as indices into some kind of database.
using key = uint32_t;

/// Assume immutable for now.
struct User {
    User(const std::string &first_name, const std::string &last_name)
        : first_name{add(first_name)}, last_name{add(last_name)} {}

    const std::string &get_first_name() const {
        return names.left.find(first_name)->second;
    }

    const std::string &get_last_name() const {
        return names.left.find(last_name)->second;
    }

    friend std::ostream &operator<<(std::ostream &os, const User &user);

protected:
    /// Instead of storing first name and last name, only store keys.
    key first_name, last_name;

    static boost::bimap<key, std::string> names;
    static key seed; // determines index for consecutive strings linearly instead of hashcode

    static key add(const std::string &s) {
        // Look for key in bimap.
        auto it = names.right.find(s);

        // If not there, insert it and return key.
        if (it == names.right.end()) {
            key id = ++seed;
            names.insert({seed, s});
            return id;
        }

        // Otherwise, just return key.
        return it->second;
    }

};

key User::seed{0};

boost::bimap<key, std::string> User::names;

std::ostream &operator<<(std::ostream &os, const User &user) {
    os << "first_name: " << user.get_first_name() << " (" << user.first_name << "), "
       << " last_name: " << user.get_last_name()  << " (" << user.last_name << ')';
    return os;
}

int main() {
    User1 user11{"John Doe"};
    User1 user12{"John Smith"};

    /// Doesn't really save us any memory.
    User2 user21{"John", "Doe"};
    User2 user22{"John", "Smith"};

    /// Now we try our real API.
    std::array<User, 5> users{
        User{"John", "Smith"},
        User{"Jane", "Smith"},
        User{"Jane", "Doe"},
        User{"Smith", "Smith"},
        User{"Wilhelmina", "Cunk"}
    };

    for (int i=0; i < users.size(); ++i)
        std::cout << "User " << i << ": " << users[i] << std::endl;
}