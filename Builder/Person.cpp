#include <ostream>

#include "Person.h"
#include "PersonBuilder.h"

/** PERSON **/
PersonBuilder Person::create() {
    return PersonBuilder();
}

