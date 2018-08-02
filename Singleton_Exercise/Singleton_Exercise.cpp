#include <cassert>
#include <functional>
#include <memory>
using namespace std;

struct SingletonTester {
    template <typename T>
    bool is_singleton(function<T*()> factory) {
        return factory() == factory();
    }
};

struct Singleton {
private:
    Singleton() {}
    static shared_ptr<Singleton> s;
public:
    static Singleton *factory() {
        return s.get();
    }

    friend std::unique_ptr<Singleton> std::make_unique<Singleton>();
};

shared_ptr<Singleton> Singleton::s = make_unique<Singleton>();

int main() {
    SingletonTester tester;
    function<Singleton*()> f = Singleton::factory;
    assert(tester.is_singleton(f));
}