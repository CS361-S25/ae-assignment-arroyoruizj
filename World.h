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

    // Constructor: Initializes the world with a random number generator
    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    // Destructor: Cleans up resources
    ~OrgWorld() {}

    // Updates the weather condition for the world
    // This function generates a random value between 0 and 1 using the random number generator
    // and assigns it to the `weather` variable. The updated weather value is then returned.
    double UpdateWeather() {
        weather = random.GetDouble(0, 1); // Generate a random weather condition
        return weather; // Return the updated weather value
    }

    // Main update function for the world
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

    // Extracts an organism from the given position and sets the position to nullptr
    emp::Ptr<Organism> ExtractOrganism(int position) {
        emp::Ptr<Organism> organism = pop[position];
        pop[position] = nullptr;
        return organism;
    }

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