#include "Organism.h"

#ifndef GRASS
#define GRASS

/**
 * @class Grass
 * @brief Represents a patch of grass, inheriting from Organism, with 
 *        instance variables water and sunshine.
 */
class Grass : public Organism {

    private:

        int water; //< The amount of water the grass has collected
        int sunshine; //< The amount of sun the grass has collected

    public:

        /**
         * @brief Constructor for the Cricket class.
         * @param _random Pointer to a random number generator.
         * @param _health Initial health value (default is 10.0).
         * @param _water Initial water value (default is 0.0).
         * @param _sunshine Initial sunshine value (default is 0.0).
         */
        Grass(emp::Ptr<emp::Random> _random, double _health=10.0, int _water=0.0, int _sunshine=0.0) : Organism(_random, _health), water(_water), sunshine(_sunshine) {}

        /**
         * @brief Get the type of the organism.
         * @return A string representing the type: "Grass".
         */
        std::string GetType() override{

            return "Grass";
        }

        /**
         * @brief Add a value to the grass's sunshine.
         * @param _in The value to add to the current sunshine.
         */
        void AddSunshine(int _in) {

            sunshine += _in;
        }

        /**
         * @brief Add a value to the grass's water supply.
         * @param _in The value to add to the current water.
         */
        void AddWater(int _in) {

            water += _in;
        }

        /**
         * @brief Process the organism's state by adding a value to its water, sunshine, and health depending on the weather.
         * @param weather The current weather in our world.
         */
        void Process(double weather) override{

            // HIGH chance of rain - we are in seattle
            // Grass gets more water, yet less sun
            if (weather < 0.5) { //Rainy Day

                AddWater(5);
                AddSunshine(3);
            } 

            // Grass gets equal amounts of water and sun
            else if (weather < 0.85) { //Cloudy Day

                AddWater(3);
                AddSunshine(3);
            }

            // Grass gets more sun, yet less water
            else { //Sunny Day

                AddWater(1);
                AddSunshine(5);
            }

            //Our grass is growing everyday, gaining health
            Organism::AddHealth(10);

        }

        /**
         * @brief Check if the grass is ready to reproduce.
         * @return A pointer to the offspring if reproduction occurs, otherwise nullptr.
         */
        emp::Ptr<Organism> CheckReproduction() override {

            if (Organism::GetHealth() >= 50 && water > 15 && sunshine > 15) {

                //Produce offspring, but also lose some health, water, and sunshine
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