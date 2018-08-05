#include <ostream>

#include "Person.h"
#include "PersonBuilder.h"

/** PERSON **/
PersonBuilder Person::create() {
    return PersonBuilder();
}

ostream &operator<<(ostream &out, const Person &p) {
    return out << p.name << " lives at: " << std::endl
               << '\t' << p.street_address << ", " << p.city << ", " << p.post_code << std::endl
               << "and works as:" << std::endl
               << '\t' << p.position << " at " << p.company_name << " with annual income $" << p.annual_income << std::endl;
}