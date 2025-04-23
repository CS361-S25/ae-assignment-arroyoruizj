#include "Organism.h"

#ifndef PREDATOR
#define PREDATOR

class Predator : public Organism {

    public:
        // Constructor
        Predator(emp::Ptr<emp::Random> _random, double _health, double _hunger) : Organism(_random, _health, _hunger) {}

        std::string GetType() const override {
            return "Predator";
        }

        // Check reproduction conditions
        emp::Ptr<Organism> CheckReproduction() override{
            constexpr double REPRODUCTION_THRESHOLD = 75.0;
            constexpr double REPRODUCTION_COST = 75.0;

            if (GetHealth() >= REPRODUCTION_THRESHOLD && GetHunger() >= REPRODUCTION_THRESHOLD) {
                emp::Ptr<Organism> offspring = emp::NewPtr<Predator>(GetRandom(), REPRODUCTION_COST, REPRODUCTION_COST);
                AddHealth(-REPRODUCTION_COST);
                AddHunger(-REPRODUCTION_COST);
                return offspring;
            }

            return nullptr;
        }
};

#endif