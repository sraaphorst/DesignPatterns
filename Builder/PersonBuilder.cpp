#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

PersonBuilderBase::PersonBuilderBase(Person &person) : person(person) {}

PersonAddressBuilder PersonBuilderBase::lives() const {
    return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder{person};
}

PersonBuilder &PersonBuilder::named(std::string name) {
    person.name = std::move(name);
    return *this;
}



PersonBuilder::PersonBuilder() : PersonBuilderBase(p) {}
