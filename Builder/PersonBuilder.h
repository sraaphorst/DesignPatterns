#pragma once

#include "Person.h"

/**
 * This is a dedicated class for building people, but we want to use it as a superclass for building person
 * address information and person employment information, but we cannot:
 *
 * You have to keep the person being built stored somewhere, and this seems like the logical choice.
 * If you inherit from it, though, you replicate the object being built up over and over and over.
 *
 * Options:
 *
 * 1. Use a pointer. (We will not do this)
 *
 * 2. Use a base class which doesn't have the object: just a reference, and a derived class, which does contain
 *    the object. This way the reference will persist, and copies will not be made, which is essential.
 *
 * We will use #2: that will allow us to inherit from PersonBuilderBase instead of PersonBuilder.
 */

// Forwards
class PersonAddressBuilder;
class PersonJobBuilder;


/**
 * This is the base class, from which our builders will come.
 */
class PersonBuilderBase {
protected:
    Person &person;
public:
    PersonBuilderBase(Person &person);

    /**
     * To cast the builder to a Person.
     */
    operator Person() const {
        return std::move(person);
    }

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};


/**
 * This is the derived class, which passes the person reference to the base class.
 * Note that this is a FACADE.
 */
class PersonBuilder : public PersonBuilderBase {
    using Self = PersonBuilder;
private:
    Person p;
public:
    PersonBuilder();

    Self &named(std::string name);
};



