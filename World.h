#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Organism.h"

class OrgWorld : public emp::World<Organism> {

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;

    public:

    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {
    }

    void Update() {

        // First, let the base World class handle its updates
        emp::World<Organism>::Update();
    
        emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    
            for (int i : schedule) {
    
                if (!IsOccupied(i)) {
    
                    continue; 
                }
    
                Organism* organism = pop[i];
                organism->Process(100);
            }
    
        // d. Create another schedule for checking reproduction after everyone has received points
        emp::vector<size_t> repro_schedule = emp::GetPermutation(random, GetSize());
    
            // Loop through the reproduction schedule
            for (size_t i : repro_schedule) {
    
                if (IsOccupied(i)) {
    
                    // e. Check if the organism reproduces
                    emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
    
                    if (offspring) {
    
                        DoBirth(*offspring, i); // Add the offspring to the population
                    
                    }
                }
            }
        }

};
#endif