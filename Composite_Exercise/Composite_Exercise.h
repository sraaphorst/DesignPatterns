#include <initializer_list>
#include <numeric>
#include <vector>

struct ContainsIntegers {
    virtual int sum() = 0;
};

struct SingleValue : ContainsIntegers {
    SingleValue(int value) : value(value) {}

    int sum() override {
        return value;
    }

private:
    int value;
};

struct ManyValues : ContainsIntegers {

    ManyValues() {}
    ManyValues(std::initializer_list<int> initializer_list) : values{initializer_list} {}

    void add(int value) {
        values.emplace_back(value);
    }

    int sum() override {
        return std::accumulate(std::begin(values), std::end(values), 0);
    }

private:
    std::vector<int> values;
};

int sum(const std::vector<ContainsIntegers*> items);