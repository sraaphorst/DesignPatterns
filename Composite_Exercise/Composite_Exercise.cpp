#include "Composite_Exercise.h"
#include <iostream>
#include <vector>

/**
 * Consider the code presented below. The sum() function takes a vector of pointers to either SingleValue
 * or ManyValues instances and adds up all their elements together.
 *
 * Please complete the implementation so that the sum() function starts to operate correctly. This may
 * involve giving the classes a common interface, amongst other things.
 *
 * Here is an example of how the function might be used:
 * SingleValue single_value{1};
 * ManyValues other_values;
 * other_values.add(2);
 * other_values.add(3);
 * sum({&single_value, &other_values}); // returns 6
 */

int sum(const std::vector<ContainsIntegers*> items) {
    int total = 0;
    for (const auto item: items)
        total += item->sum();
    return total;
}

int main() {
    SingleValue sv1{10};
    SingleValue sv2{15};
    ManyValues  mv1{1, 2, 3, 4, 5};
    ManyValues  mv2{6, 7, 8, 9, 10};
    std::vector<ContainsIntegers*> v{&sv1, &mv1, &sv2, &mv2};
    std::cout << "sum is: " << sum(v) << std::endl;
}