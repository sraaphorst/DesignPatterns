#include <string>
#include <iostream>
using namespace std;

struct Person {
    int id;
    string name;

    friend ostream &operator<<(ostream &os, const Person &person) {
        os << "id: " << person.id << " name: " << person.name;
        return os;
    }
};

class PersonFactory {
private:
    int id = 0;
public:
    Person create_person(const string &name) {
        return {id++, name};
    }
};

int main() {
    PersonFactory pf;
    cout << pf.create_person("Henry") << endl
         << pf.create_person("Felix") << endl;
}