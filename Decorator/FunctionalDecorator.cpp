/**
 * Provide a decorator around a function to, say, produce logging.
 */
#include <iostream>
#include <functional>
#include <string>

struct Logger1 {
    std::function<void()> func;
    std::string name;

    Logger1(const std::function<void()> func, const std::string &name)
        : func{func}, name{name} {}

    void operator()() const {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

/// Logger2 is for a function with void return type but takes arguments.
template<typename Func>
struct Logger2 {
    Func func;
    std::string name;

    Logger2(const Func &func, const std::string &name)
            : func{func}, name{name} {}

    template<typename...Args>
    void operator()(Args... args) const {
        std::cout << "Entering " << name << std::endl;
        func(args...);
        std::cout << "Exiting " << name << std::endl;
    }
};

/// Helper function lets you infer type of func.
template<typename Func>
auto make_logger2(Func &func, const std::string &name) {
    return Logger2<Func>{func, name};
}

double add(double a, double b) {
    std::cout << a << " + " << b << " = " << a + b << std::endl;
    return a + b;
}

double add4(double a, double b, double c, double d) {
    return a + b + c + d;
}

/// Logger3 takes one typename, but it is composed of multiple typenames.
template<typename> struct Logger3;
template<typename R, typename... Args>
struct Logger3<R(Args...)> {
    std::function<R(Args...)> func;
    std::string name;

    Logger3(const std::function<R(Args...)> &func, const std::string &name) : func{func}, name{name} {}

    R operator()(Args... args) const {
        std::cout << "Entering " << name << std::endl;
        R val = func(args...);
        std::cout << "Exiting " << name << std::endl;
        return val;
    }
};

struct adder {
    int a, b;
    int operator()(int c) {
        return a + b + c;
    }
};

/// Need a helper to figure out args of template class.
template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const std::string name) {
    return Logger3<R(Args...)>(std::function<R(Args...)>(func), name);
}

int main() {
    // void(void)
    Logger1{[] { std::cout << "Hello" << std::endl;}, "HelloFunction"}();

    // void(param)
    // Still don't need make_logger2.
    auto loggedGreeter = Logger2{[](const std::string &name) { std::cout << "Hello, " << name << '!' << std::endl; },
                                       "GreeterFunction"};
    loggedGreeter("Steve");

    // We seem to be able to create this, but not do anything with it.
    // This is all very confusing.
    adder a{1,2};
    auto log_struct = Logger2(adder{1,2}, "LA");
    auto log_struct2 = Logger2([&a](int c) { return a(c); }, "poop");
    log_struct2(3);

    // This works just fine.
    auto log_add2 = make_logger3(add, "Add");
    auto log_add2_result = log_add2(1,2);
    std::cout << "The result is " << log_add2_result << std::endl;

    // We can now extrapolate to bigger types, but this doesn't seem to work with lambdas.
    auto log_add4 = make_logger3(add4, "add4");
    auto log_add4_result = log_add4(1, 2, 3, 4);
    std::cout << "The result is " << log_add4_result << std::endl; }