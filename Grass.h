#include "Organism.h"

#ifndef GRASS
#define GRASS

class Grass : public Organism {

    private:

        int water;
        int sunshine;

    public:

        Grass(emp::Ptr<emp::Random> _random, double _health=10.0, int _water=0.0, int _sunshine=0.0) : Organism(_random, _health), water(_water), sunshine(_sunshine) {}

        std::string GetType() override{

            return "Grass";
        }

        void AddSunshine(int _in) {

            sunshine += _in;
        }

        void AddWater(int _in) {

            water += _in;
        }

        void Process(double weather) override{
            
            if (weather < 0.5) { //rainy, we are in seattle

                AddWater(5);
                AddSunshine(3);
            } 

            else if (weather < 0.85) { //cloud

                AddWater(3);
                AddSunshine(3);
            }

            else { //sunny

                AddWater(1);
                AddSunshine(5);
            }

            Organism::AddHealth(10);

        }

        emp::Ptr<Organism> CheckReproduction() override {

            if (Organism::GetHealth() >= 50 && water > 15 && sunshine > 15) {

                emp::Ptr<Organism> offspring = new Grass(Organism::GetRandom());
                Organism::AddHealth(-50);
                AddWater(-15);
                AddSunshine(-15);

                return offspring;
            }

            return nullptr;
        }
};

#endif