#ifndef ORGANISM_H
#define ORGANISM_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {

    private:

        double health;
        emp::Ptr<emp::Random> random;

    public:

        Organism(emp::Ptr<emp::Random> _random, double _health=0.0) :
            health(_health), random(_random) {;}

        virtual std::string GetType() {

            return "Organism";
        }

        double GetHealth() {
            
            return health;
        }

        emp::Ptr<emp::Random> GetRandom() {

            return random;

        }

        void SetHealth(double _in) {
            
            health = _in;
        }

        void AddHealth(double _in) {
            
            health += _in;
        }

        virtual void Process(double _in) {
            
            AddHealth(_in);
        
        }

        virtual emp::Ptr<Organism> CheckReproduction() {

            if (health >= 1000) {

                emp::Ptr<Organism> offspring = new Organism(random, 0);
                health = health - 1000;
                return offspring;
            }

            return nullptr;
        }
};
#endif