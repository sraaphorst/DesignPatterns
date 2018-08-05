/**
 * Person.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

#include <iostream>
#include <memory>

#include "Person.h"

/**
 * Why would we do this?
 * Hide implementation details of the Person class.
 * If not doing pimpl, would have private section in Person with
 *   lots of secret functions, which are still revealed in header.
 *
 * Another improvement is compilation speed. Allows us to change
 * implementations without changing the surface API, so no binary
 * incompatibility produced.
 *
 * Thus, you can make changes to implementations, recompile, and
 * just send new binaries to users, instead of forcing them to
 * update entire installation.
 */
class Person::PersonImpl {
public:
    void greet(Person *p);
private:
    /// All the secret details in here...
};


void Person::PersonImpl::greet(Person *p) {
    std::cout << "Hello. My name is " << p->name << '.'  << std::endl;
}

Person::Person(const std::string &name)
    : name{name}, impl{std::make_shared<PersonImpl>()} {}

Person::Person(std::string &&name)
    : name{std::move(name)}, impl{std::make_shared<PersonImpl>()} {}

void Person::greet() {
    impl->greet(this);
}


int main() {
    Person seb{"Sebastian"};
    seb.greet();
}