#include <common.h>
#include <memory>
#include <string>

#pragma once

/**
 * Pimpl idiom: implementation of Person is actually deferred or relayed or bridged into a separate class.
 */
class Person {
public:
    std::string name;

    /// Person is bridged into this implementation object.
    class PersonImpl;
    std::shared_ptr<PersonImpl> impl;

    Person(const std::string &name);
    Person(std::string&& name);
    ~Person() = default;

    void greet();
};