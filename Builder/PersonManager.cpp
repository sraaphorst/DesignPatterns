#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

using namespace std;

int main() {
    /**
     * Our goal is to write something like the following, where we will jump from one builder
     * to the other.
     *
     * lives() gives us the PersonAddressBuilder.
     * works() gives us the PersonJobBuilder.
     *
     * Final step is to cast the builder to a final person.
     **/
    Person p = Person::create()
            .named("Felix Yagunglepuss")
            .lives().at("123 London Road")
                    .with_postcode("SW1 1GB")
                    .in("London")
            .works().at("Pragmasoft")
                    .as_a("Consultant")
                    .earning(1e7);

    cout << p;
}