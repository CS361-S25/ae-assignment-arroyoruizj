#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Organism.h"

class OrgWorld : public emp::World<Organism> {

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;
    double weather;

    public:

    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {}

    double UpdateWeather() {

        weather = random.GetDouble(0, 1);

        return weather;
    }

    void Update() {

        // First, let the base World class handle its updates
        emp::World<Organism>::Update();

        double current_weather = UpdateWeather();

        emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    
            for (int i : schedule) {
    
                if (!IsOccupied(i)) {
    
                    continue; 
                }
    
                emp::Ptr<Organism> organism = ExtractOrganism(i);
                organism->Process(current_weather);
                emp::WorldPosition randNeighborPos = GetRandomNeighborPos(i);
                AddOrgAt(organism, randNeighborPos);
            }
    
        // d. Create another schedule for checking reproduction after everyone has received health
        emp::vector<size_t> repro_schedule = emp::GetPermutation(random, GetSize());
    
            // Loop through the reproduction schedule
            for (size_t i : repro_schedule) {
    
                if (IsOccupied(i)) {
    
                    // e. Check if the organism reproduces
                    emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
    
                    if (offspring) {
    
                        AddOrgAt(offspring, GetRandomNeighborPos(i)); // Add the offspring to the population
                    
                    }
                }
            }
        }

        emp::Ptr<Organism> ExtractOrganism(int position) {

            emp::Ptr<Organism> organism = pop[position];
            pop[position] = nullptr;

            return organism;
        }

};
#endif