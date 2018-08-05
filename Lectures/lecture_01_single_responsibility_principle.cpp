#include "common.h"

/*** SINGLE RESPONSIBILITY PRINCIPLE ***/

// Journal to store our most private thoughts.
struct Journal {
    string title;
    vector<string> entries;

    Journal(const string &title) : title(title) {}

    void add_entry(const string &entry) {
        static int count = 1;
        entries.push_back(lexical_cast<string>(count++) + ": " + entry);
    }

    /**
     * By implementing save here, you have added a separate concern, i.e. persistence into your journal.
     * Imagine you had another dozen objects with functions called save and load.
     * Problem: when you want to change persistence, you have to change persistence in all of those classes!
     * (Example: decide to use DBs instead of files for saving.)
     *
     * Thus, instead, we do SEPARATION OF CONCERNS:
     * Journal manages journal entry and journal contents.
     * For persistence, we introduce a separate component.
     */
    void bad_idea_save(const string &filename) {
        // ...
    }
};

/**
 * The one central location where objects are loaded and saved.
 * Then we can change the manner of persistence (e.g. using database instead of files) and make change only here!
 */
struct PersistenceManager {
    static void save(const Journal &j, const string &filename) {
        ofstream ofs(filename);
        ofs << j.title << endl;
        for (auto &e: j.entries) {
            ofs << e << endl;
        }
    }
};

int main() {
    Journal journal{"Dear diary"};
    journal.add_entry("I ate a bug");
    journal.add_entry("I cried today");

    // Now, instead of saying:
    // journal.bad_idea_save("diary.txt");
    // we do:
    PersistenceManager::save(journal, "diary.txt");

    return 0;
}