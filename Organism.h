#include <string>

#ifndef ORGANISM
#define ORGANISM

class Organism {

    private:

        double health;
        emp::Ptr<emp::Random> random;


    public: 

        Organism(double _health) : health(_health) {}

        virtual std::string GetType() {

            return "Organism";

        }

        virtual double GetHealth() {

            return health;

        }

        void Process (double add_points) {

            health = health + add_points;

        }

};

#endif