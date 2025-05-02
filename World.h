#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"
#include "Organism.h"

class OrgWorld : public emp::World<Organism> {

    emp::Random &random; // Reference to the random number generator
    emp::Ptr<emp::Random> random_ptr; // Pointer to the random number generator
    double weather; // Variable to store the current weather condition

    public:

    /**
     * @brief Constructor for the World class.
     * @param _random Pointer to a random number generator.
     */
    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    // Destructor: Cleans up resources
    ~OrgWorld() {}

    /**
     * @brief Function to update the weather condition.
     * @return The updated weather value.
     */
    double UpdateWeather() {
        weather = random.GetDouble(0, 1); // Generate a random weather condition
        return weather; // Return the updated weather value
    }

     /**
     * @brief Main update function for the world.
     * World begins by updating weather for each "day" (step), simulating the effects of
     * weather on the organisms. Then, we process if any crickets eat grass, and finally
     * check if any organisms can reproduce.
     */
    void Update() {

        // First, let the base World class handle its updates
        emp::World<Organism>::Update();

        double current_weather = UpdateWeather();
        emp::vector<size_t> weather_schedule = emp::GetPermutation(random, GetSize());
        ProcessWeather(weather_schedule, current_weather);

        // Generate a random schedule for organisms to eat
        emp::vector<size_t> eat_schedule = emp::GetPermutation(random, GetSize());
        ProcessEating(eat_schedule);


        // Generate a random schedule for checking reproduction
        emp::vector<size_t> repro_schedule = emp::GetPermutation(random, GetSize());
        ProcessReproduction(repro_schedule);
    
    }
    /**
     * @brief Function to get a random neighbor position for an organism.
     * @param pos The current position of the organism.
     * @return A random neighbor position.
     */
    emp::Ptr<Organism> ExtractOrganism(int position) {
        emp::Ptr<Organism> organism = pop[position];
        pop[position] = nullptr;
        return organism;
    }

    /**
     * @brief Function to process the weather for each organism.
     * @param _weather_sched The schedule of organisms to process.
     * @param _weather The current weather condition.
     */
    void ProcessWeather (emp::vector<size_t> _weather_sched, double _weather) {

        for (int i : _weather_sched) {
    
            if (!IsOccupied(i)) {
                continue; // Skip empty positions
            }
            
            // Extract the organism at the current position
            emp::Ptr<Organism> organism = ExtractOrganism(i);
            organism->Process(_weather); // Process the organism with the current weather

            // If the organism is a Cricket, move it to a random neighbor position
            if (organism->GetType() == "Cricket") {
                emp::WorldPosition randNeighborPos = GetRandomNeighborPos(i);
                AddOrgAt(organism, randNeighborPos);
            } else {
                // Otherwise, add it back to its original position
                AddOrgAt(organism, i);
            } 
        }
    }

    /**
     * @brief Function to process the eating behavior of organisms.
     * @param _eating_sched The schedule of organisms to process for eating.
     */
    void ProcessEating (emp::vector<size_t> _eating_sched) {

        for (int i : _eating_sched) {

            if (!IsOccupied(i)) {
                continue; // Skip empty positions
            }
            
            // Get the organism at the current position without extracting it
            emp::Ptr<Organism> organism = pop[i];

            // If the organism is a Cricket, let it eat its neighbors
            if (organism->GetType() == "Cricket") {
                emp::vector<size_t> neighbors = GetValidNeighborOrgIDs(i);

                for (int neighborIndex : neighbors) {
                    if (pop[neighborIndex]) {
                        // Extract the neighbor organism and let the Cricket eat it
                        emp::Ptr<Organism> neighbor = ExtractOrganism(neighborIndex);
                        organism->Eat(neighbor);
                    }
                }
            }
        }
    }

    /**
     * @brief Function to process the reproduction of organisms.
     * @param _repro_sched The schedule of organisms to process for reproduction.
     */
    void ProcessReproduction (emp::vector<size_t> _repro_sched) {

         // Loop through the reproduction schedule
        for (size_t i : _repro_sched) {

            if (IsOccupied(i)) {

                // Check if the organism reproduces
                emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();

                if (offspring) {
                    // Add the offspring to a random neighbor position
                    AddOrgAt(offspring, GetRandomNeighborPos(i));
                }
            }
        }
    }

};

#endif