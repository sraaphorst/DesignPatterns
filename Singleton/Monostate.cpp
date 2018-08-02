#include <common.h>

/**
 * Monostate is an interesting variation of the Singleton pattern.
 */

/**
 * We make Printer look like an ordinary class, with the data all being static storage.
 * Users will be interacting with this normally.
 * Behind the scene, all of this interaction is going through a static member.
 */
class Printer {
    static int id;

public:
    int get_id() const { return id; }
    void set_id(int value) { id = value; }
};

int Printer::id = 0;

/**
 * Lots of reasons why this is a terrible ideaL e.g. inheritance.
 * In this case, the only things inherited are methods and not the id.
 * Also, the client is not really informaed that this is a singleton.
 */
int main() {
    Printer p1;
    Printer p2;
    p2.set_id(1);

    cout << "Printer1 id: " << p1.get_id() << endl
         << "Printer2 id: " << p2.get_id() << endl;
}