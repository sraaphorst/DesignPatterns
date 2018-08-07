/**
 * This falls in the intersection of Composite and Proxy patterns.
 */

#include <algorithm>
#include <array>
#include <numeric>
#include <ostream>
#include <iostream>

/// Let's say we have a creature in a video game:
class Creature {
    std::string name;
    int strength;
    int intelligence;
    int agility;

public:
    explicit Creature(const std::string &name) : name(name) {}

    int getStrength() const {
        return strength;
    }

    void setStrength(int strength) {
        Creature::strength = strength;
    }

    int getIntelligence() const {
        return intelligence;
    }

    void setIntelligence(int intelligence) {
        Creature::intelligence = intelligence;
    }

    int getAgility() const {
        return agility;
    }

    void setAgility(int agility) {
        Creature::agility = agility;
    }

    /**
     * Sometimes we want to perform aggregate calculations.
     * This becomes quite painful and doesn't scale well.
     * If we want to add, say, charisma, we have to change everything.
     */
     int sum() const {
         return strength + intelligence + agility;
     }

     double average() const {
         return sum() / 3.0;
     }

     int max() const {
         /// Uses initializer list.
         return std::max({strength, intelligence, agility});
     }
};

/**
 * Instead, we rewrite using properties, not storing each trait as a specialized field.
 */
class BetterCreature {
    std::string name;
    /// count indicates the number of abilities. Do not use scoped enums here or this won't work without lots of casting.
    /// Using a regular enum allows us to treat the values as ints.
    enum Abilities {
        strength, agility, intelligence, count,
        };

    std::array<int, Abilities::count> abilities;

public:
    explicit BetterCreature(const std::string &name) : name(name) {}

    /// Now unfortunately, we have to write the getters and setters by hand as CLion cannot handle the generation.
    int getStrength() const {
        return abilities[strength];
    };

    void setStrength(int val) {
        abilities[strength] = val;
    }

    int getAgility() const {
        return abilities[agility];
    };

    void setAgility(int val) {
        abilities[agility] = val;
    }

    int getIntelligence() const {
        return abilities[intelligence];
    };

    void setIntelligence(int val) {
        abilities[intelligence] = val;
    }

    /// However, the rest of the functions become trivially easy.
    int sum() const {
        return std::accumulate(abilities.cbegin(), abilities.cend(), 0);
    }

    double average() const {
        return sum() / count;
    }

    int max() const {
        /// Remember max_element returns an iterator.
        return *std::max_element(std::cbegin(abilities), std::cend(abilities));
    }

    friend std::ostream &operator<<(std::ostream &os, const BetterCreature &creature) {
        os << "The " << creature.name << " has "
           << "a strength of " << creature.getStrength() << ", "
           << "an agility of " << creature.getAgility() << ", "
           << "and an intelligence of " << creature.getIntelligence() << "." << std::endl
           << "\tThe difficulty level is " << creature.sum()
           << ", with avg ability " << creature.average()
           << " and max ability " << creature.max() << '.' << std::endl;

        return os;
    }
};


int main() {
    BetterCreature orc{"orc"};
    orc.setStrength(18);
    orc.setAgility(11);
    orc.setIntelligence(5);
    std::cout << orc;
}