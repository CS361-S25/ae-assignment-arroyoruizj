#include "Organism.h"

#ifndef CRICKET
#define CRICKET

/**
 * @class Cricket
 * @brief Represents a basic cricket, inheriting from Organism, with 
 *        an instance variable hunger.
 */
class Cricket : public Organism {

    private:

        int hunger; ///< The hunger level of the organism.

    public:

        /**
         * @brief Constructor for the Cricket class.
         * @param _random Pointer to a random number generator.
         * @param _health Initial health value (default is 10.0).
         * @param _hunger Initial hunger value (default is 0.0).
         */
        Cricket(emp::Ptr<emp::Random> _random, double _health=10.0, double _hunger=0.0) : Organism(_random, _health), hunger(_hunger) {}

        /**
         * @brief Get the type of the organism.
         * @return A string representing the type: "Cricket".
         */
        std::string GetType() override{

            return "Cricket";
        }

        /**
         * @brief Add a value to the organism's hunger.
         * @param _in The value to add to the current hunger.
         */
        void AddHunger(int _in) {

            hunger += _in;
        }

        /**
         * @brief Process the organism's state by adding a value to its health and hunger depending on the weather.
         * @param weather The current weather in our world.
         */
        void Process(double weather) override{
            
            // HIGH chance of rain - we are in seattle
            // Cricket has to spend more energy when it's raining -> gains more hunger
            if (weather < 0.5) { //Rainy Day

                AddHunger(5);
            } 

            // Perfect weather for eating grass! -> less hunger
            else if (weather < 0.85) { //Cloudy Day

                AddHunger(2);
            }

            // Cricket has to spend more energy when it's too sunny -> gains more hunger
            else { //Sunny Day

                AddHunger(5);
            }

            //Our cricket is growing everyday, gaining health
            Organism::AddHealth(5);
            
        }

        /**
         * @brief Perform an eating action with a neighboring organism.
         * @param neighbor Pointer to the neighboring organism.
         */
        void Eat(emp::Ptr<Organism> neighbor) override{

            if (neighbor->GetType() == "Grass") { //Eats grass -> decrease hunger and add health

                AddHealth(10);
                AddHunger(-5);

            } else { //Spent energy looking for grass -> gain hunger

                AddHunger(1);
            }
        }

        /**
         * @brief Check if the cricket is ready to reproduce.
         * @return A pointer to the offspring if reproduction occurs, otherwise nullptr.
         */
        emp::Ptr<Organism> CheckReproduction() override {

            if (Organism::GetHealth() >= 75 && hunger <= 25) {

                //Produce offspring, but also lose some health and gain hunger
                emp::Ptr<Organism> offspring = new Cricket(Organism::GetRandom());
                Organism::AddHealth(-75);
                AddHunger(25);
                return offspring;
            }

            return nullptr;
        }
};

#endif