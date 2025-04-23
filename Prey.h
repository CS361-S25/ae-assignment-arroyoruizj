#include "Organism.h"

#ifndef PREY
#define PREY

class Prey : public Organism {

    public:
        // Constructor
        Prey(emp::Ptr<emp::Random> _random, double _health, double _hunger)
            : Organism(_random, _health, _hunger) {}

        // Override GetType with const correctness
        std::string GetType() {
            
            return "Prey";
        
        }

        // Check reproduction conditions
        emp::Ptr<Organism> CheckReproduction() override {
            constexpr double REPRODUCTION_THRESHOLD = 50.0;
            constexpr double REPRODUCTION_COST = 50.0;

            if (GetHealth() >= REPRODUCTION_THRESHOLD && GetHunger() >= REPRODUCTION_THRESHOLD) {
                emp::Ptr<Organism> offspring = emp::NewPtr<Prey>(GetRandom(), REPRODUCTION_COST, REPRODUCTION_COST);
                AddHealth(-REPRODUCTION_COST);
                AddHunger(-REPRODUCTION_COST);
                return offspring;
            }

            return nullptr;
        }
};

#endif