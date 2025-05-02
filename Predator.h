#include "Organism.h"

#ifndef PREDATOR
#define PREDATOR

class Predator : public Organism {

    double hunger;

    public:

        Predator(double _health, double _hunger) : Organism(_health), hunger(_hunger) {}

        std::string GetType() const {

            return "Predator";

        }

        double GetHunger() {

            return hunger;

        }

};

#endif