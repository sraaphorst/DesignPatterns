#pragma once

#include <string>
#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilderBase {
    using Self = PersonAddressBuilder;

public:
    explicit PersonAddressBuilder(Person &person) : PersonBuilderBase{person} {}

    Self &at(string street_address) {
        person.street_address = std::move(street_address);
        return *this;
    }

    Self &with_postcode(string post_code) {
        person.post_code = std::move(post_code);
        return *this;
    }

    Self &in(string city) {
        person.city = std::move(city);
        return *this;
    }
};