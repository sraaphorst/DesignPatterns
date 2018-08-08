/**
 * Instead of building bimaps, you can just use a library solution as this problem has been
 * addressed many times before. There is actually a boost flyweight solution.
 */
#include <boost/flyweight.hpp>

#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

struct User {
    boost::flyweight<std::string> first_name;
    boost::flyweight<std::string> last_name;

    /// You can assign a flyweight<string> from string and print it to the command line without issues.
    User(const std::string &first_name, const std::string &last_name)
        : first_name(first_name), last_name(last_name) {}

    friend std::ostream &operator <<(std::ostream &str, const User &user);
};

std::ostream &operator <<(std::ostream &str, const User &user) {
    str << user.first_name << " " << user.last_name;
    return str;
}

int main() {
    std::array<User, 5> users{
            User{"John", "Smith"},
            User{"Jane", "Smith"},
            User{"Jane", "Doe"},
            User{"Smith", "Smith"},
            User{"Wilhelmina", "Cunk"}
    };

    for (int i=0; i < users.size(); ++i)
        std::cout << "User " << i << ": " << users[i] << std::endl;

    /// We can compare the pointers to see that the flyweight actually works.
    std::cout << std::boolalpha;
    std::cout << (&users[0].first_name.get() == &users[1].first_name.get()) << std::endl;
    std::cout << (&users[0].last_name.get()  == &users[1].last_name.get()) << std::endl;
}