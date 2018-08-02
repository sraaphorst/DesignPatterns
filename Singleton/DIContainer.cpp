#include <common.h>

/**
 * Instead of defining your singleton explicitly by hiding constructors and implementing get method is that we can
 * work with a version controlled container used in a dependency injection framework to make a dependency injection
 * for us. This works on the principle of having different containers with different lifetimes, and a singleton is
 * a special case of this: i.e. a container with only one component existing at any one time.
 */

// See Boost.DI: dependency injection.
// http://boost-experimental.github.io/di
#include "di.hpp"
using namespace boost::di;

/**
 * We now show how we can configure a component to have a singleton lifetime and how we can verify that it is a
 * singleton.
 */
struct IFoo {
    virtual string name() = 0;
};

/**
 * Check that only one Foo is ever created through the id.
 */
struct Foo : public IFoo {
    static int id;
    Foo() { ++id; }

    /**
     * Not 100% sure why we have the string literal suffix s:
     * https://en.cppreference.com/w/cpp/string/basic_string/operator%22%22s
     */
    string name() override {
        return "foo "s + lexical_cast<string>(id);
    }
};

int Foo::id = 0;

/**
 * Bar needs a singleton instance of Foo.
 * We will use the Boost di framework for this instead of making our own singleton.
 */
struct Bar {
    // Instance of foo will be injected here.
    std::shared_ptr<IFoo> foo;
};

int main() {
    // Last parameter specifies lifetime.
    auto injector = di::make_injector(
            di::bind<IFoo>().to<Foo>().in(di::singleton)
            );

    auto bar1 = injector.create<std::shared_ptr<Bar>>();
    auto bar2 = injector.create<std::shared_ptr<Bar>>();

    cout << bar1->foo->name() << endl;
    cout << bar2->foo->name() << endl;

    // In this case, we can just compare pointers, since we are using shared_ptr and they are pointing
    // towards the same object
    cout << boolalpha << (bar1->foo.get() == bar2->foo.get());
}