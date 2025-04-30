#include "Organism.h"

#ifndef CRICKET
#define CRICKET

class Cricket : public Organism {

    private:

        int hunger;

    public:

        Cricket(emp::Ptr<emp::Random> _random, double _health=10.0, double _hunger=0.0, int _fitness=1) : Organism(_random, _health), hunger(_hunger) {}

        std::string GetType() override{

            return "Cricket";
        }

        double GetHunger() {

            return hunger;
        }

        void AddHunger(int _in) {

            hunger += _in;
        }

        void Process(double weather) override{
            
            if (weather < 0.5) { //rainy, we are in seattle

                AddHunger(3);
            } 

            else if (weather < 0.85) { //cloud

                AddHunger(2);
            }

            else { //sunny

                AddHunger(3);
            }

            Organism::AddHealth(5);
            
        }

        void Eat(emp::Ptr<Organism> neighbor) override{

            if (neighbor->GetType() == "Grass") {

                AddHealth(10);
                AddHunger(-5);

            } else {

                AddHunger(1);
            }
        }

        emp::Ptr<Organism> CheckReproduction() override {

            if (Organism::GetHealth() >= 75 && hunger <= 25) {

                emp::Ptr<Organism> offspring = new Cricket(Organism::GetRandom());
                Organism::AddHealth(-750);
                return offspring;
            }

            return nullptr;
        }
};

#endif