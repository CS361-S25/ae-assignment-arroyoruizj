#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"
#include <string>

#ifndef ORGANISM
#define ORGANISM

class Organism {

    protected: // Changed to protected for easier access in derived classes
        double health;
        double hunger;
        emp::Ptr<emp::Random> random;

    public:
        // Constructor with initialization list
        Organism(emp::Ptr<emp::Random> _random, double _health, double _hunger)
            : random(_random), health(_health), hunger(_hunger) {}

        // Virtual destructor
        virtual ~Organism() {}

        // Virtual method for type
        virtual std::string GetType() const {
            return "Organism";
        }

        virtual emp::Ptr<Organism> CheckReproduction() {
            // Default implementation: no reproduction
            return nullptr;
        }

        // Getters with const correctness
        double GetHealth() const {
            return health;
        }

        double GetHunger() const {
            return hunger;
        }

        emp::Ptr<emp::Random> GetRandom() const {
            return random;
        }

        // Modifiers
        void AddHealth(double _in) {
            health += _in;
        }

        void AddHunger(double _in) {
            hunger += _in;
        }
};

#endif
