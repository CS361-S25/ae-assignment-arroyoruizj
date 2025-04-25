#include "Organism.h"

#ifndef CRICKET
#define CRICKET

class Cricket : public Organism {

    private:

        int hunger;
        int fitness;

    public:

        Cricket(emp::Ptr<emp::Random> _random, double _health=10.0, double _hunger=0.0, int _fitness=1) : Organism(_random, _health), hunger(_hunger), fitness(_fitness) {}

        std::string GetType() override{

            return "Cricket";
        }

        double GetHunger() {

            return hunger;
        }

        void AddHunger(int _in) {

            hunger += _in;
        }

        int Getfitness() {

            return fitness;
        }

        void SetFitness(int _fitness) {

            fitness = _fitness;
        }

        void Process(double weather) {
            
            if (weather < 0.5) { //rainy, we are in seattle

                SetFitness(1);
            } 

            else if (weather < 0.85) { //cloud

                SetFitness(2);
            }

            else { //sunny

                SetFitness(3);
            }

            Organism::AddHealth(5);
            AddHunger(5);
        }

        emp::Ptr<Organism> CheckReproduction() override{

            if ((Organism::GetHealth() >= 50) && (hunger <= 25)) {

                emp::Ptr<Organism> offspring = new Cricket(Organism::GetRandom());
                Organism::AddHealth(-50);
                AddHunger(25);
                SetFitness(1);
                return offspring;
            }

            return nullptr;
        }
};

#endif