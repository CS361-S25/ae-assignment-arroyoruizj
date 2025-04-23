#include "Organism.h"

#ifndef PREY
#define PREY

class Prey : public Organism {

    double energy;

    public:

        Prey(double _health, double _energy) : Organism(_health), energy(_energy) {}

        std::string GetType() const {

            return "Prey";

        }

        double GetEnergy() {

            return energy;

        }

};

#endif