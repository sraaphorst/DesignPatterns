#include "exercise.h"
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
    SingleValue single_value{1};
    ManyValues other_values;
    other_values.add(2);
    other_values.add(3);
    int s = sum({&single_value, &other_values});
    std::cout << s << std::endl;
}