#include <common.h>
#include <gtest/gtest.h>

/**
 * The singleton is not a bad idea: it's only a bad idea when we have a hard dependency on it.
 * In this case, this is why we create the IDatabase interface and the DummyDatabase, as this
 * removes the dependency on the actual database, which could change and thus ruin our tests.
 */

/**
 * We solve the problem of dependency (below) on our singleton (which creates an integration test when we want a unit
 * test) by creating a dummy database. First, begin with an interface.
 */
class IDatabase {
public:
    virtual int get_population(const string &city) = 0;
};

/**
 * For some components, it makes sense to only have one in the system, e.g.:
 * 1. Database repository.
 * 2. Object factory (has no state).
 *
 * Best for when constructor call is expensive and something we only want to do once.
 * Then we want to provide everyone with the same instance.
 * Need to take care of lazy instantiation and thread safety.
 */
class SingletonDatabase : public IDatabase {
private:
    SingletonDatabase() {
        cout << "Initializing database..." << endl;
        ifstream ifs("capitals.txt");
        string s, s2;
        while (getline(ifs, s)) {
            getline(ifs, s2);
            int pop = lexical_cast<int>(s2);
            capitals[s] = pop;
        }
    }

    map<string, int> capitals;

public:
    /**
     * We also need to delete the copy constructor and copy assignment to avoid copying.
     */
    SingletonDatabase(const SingletonDatabase&) = delete;
    void operator=(const SingletonDatabase&) = delete;

    static SingletonDatabase &get() {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const string &city) {
        return capitals[city];
    }
};

/**
 * Here is our dummy databasse.
 */
class DummyDatabase : public IDatabase {
private:
    map<string, int> capitals;

public:
    DummyDatabase() {
        capitals["alpha"] = 1;
        capitals["beta"] = 2;
        capitals["gamma"] = 3;
    }

    int get_population(const string &city) override {
        return capitals[city];
    }
};

/**
 * Problems show up when we want to test this.
 */
struct SingletonRecordFinder {
    int total_population(vector<string> names) {
        int result = 0;
        for (auto &name: names)
            result += SingletonDatabase::get().get_population(name);
        return result;
    }
};

/**
 * Instead of having direct access to the singleton, we want a dependency: hence, the dependency injection.
 */
struct ConfigurableRecordFinder {
private:
    IDatabase &db;

public:
    ConfigurableRecordFinder(IDatabase &db) : db(db) {}

    /**
     * Note here that we use the DB passed in instead of specifically the singleton.
     * This allows unit test instead of integration test.
     */
    int total_population(vector<string> names) {
        int result = 0;
        for (auto &name: names)
            result += db.get_population(name);
        return result;
    }
};

/***** Google Tests ******/
/**
 * We are strongly tied to the actual database. Thus singleton total population test is not a unit test, but an
 * integration test. We cannot unentangle the two to get a proper unit test. If the file changes, we are in trouble.
 * We will use instead dependency injection by using a dummy database instead of the real database.
 */
 TEST(RecordFinderTests, SingletonTotalPopulationTest) {
   SingletonRecordFinder rf;
   vector<string> names { "Seoul", "Mexico City" };
   int tp = rf.total_population(names);
   EXPECT_EQ(17500000 + 17400000, tp);
 }

/**
 * Here is the test using the (non-changing) dummy database.
 */
TEST(RecordFinderTests, DependentTotalPopulationTest) {
    DummyDatabase db;
    ConfigurableRecordFinder rf{db};

    // We are not dependent on the actual database here, i.e. on capitals.txt.
    // Thus, the database (capitals.txt) can change and our test will still function.
    EXPECT_EQ(4, rf.total_population(vector<string>{"alpha", "gamma"}));
}

/**
 * Google tests: can either do this, or omit main and link to gtest_main.
 */
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}