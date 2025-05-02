#ifndef ORGANISM_H
#define ORGANISM_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

/**
 * @class Organism
 * @brief Represents a basic organism with health and random number generator.
 */
class Organism {

    private:

        double health; ///< The health level of the organism.
        emp::Ptr<emp::Random> random; ///< Pointer to a random number generator.

    public:

        /**
         * @brief Constructor for the Organism class.
         * @param _random Pointer to a random number generator.
         * @param _health Initial health value (default is 0.0).
         */
        Organism(emp::Ptr<emp::Random> _random, double _health=0.0) :
            health(_health), random(_random) {;}

        /**
         * @brief Get the type of the organism.
         * @return A string representing the type of the organism.
         */
        virtual std::string GetType() {

            return "Organism";
        }

        /**
         * @brief Get the current health of the organism.
         * @return The health value as a double.
         */
        double GetHealth() {
            
            return health;
        }

        /**
         * @brief Get the random number generator associated with the organism.
         * @return A pointer to the random number generator.
         */
        emp::Ptr<emp::Random> GetRandom() {

            return random;

        }

        /**
         * @brief Add a value to the organism's health.
         * @param _in The value to add to the current health.
         */
        void AddHealth(double _in) {
            
            health += _in;
        }

        /**
         * @brief Process the organism's state by adding a value to its health.
         * @param _in The value to add to the organism's health.
         */
        virtual void Process(double _in) {
            
            AddHealth(_in);
        
        }

        /**
         * @brief Perform an eating action with a neighboring organism.
         * @param neighbor Pointer to the neighboring organism.
         */
        virtual void Eat(emp::Ptr<Organism> neighbor) {}

        /**
         * @brief Check if the organism is ready to reproduce.
         * @return A pointer to the offspring if reproduction occurs, otherwise nullptr.
         */
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