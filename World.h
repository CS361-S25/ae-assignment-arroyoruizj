#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Organism.h"
#include "Prey.h"
#include "Predator.h"

class OrgWorld : public emp::World<Organism> {
    emp::Random &random;

public:
    OrgWorld(emp::Random &_random)
        : emp::World<Organism>(_random), random(_random) {}

    ~OrgWorld() {}

    void Update() {
        // First, let the base World class handle its updates
        emp::World<Organism>::Update();

        // a. Process each organism
        emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
        for (size_t i : schedule) {
            if (!IsOccupied(i)) continue;
            Organism* organism = pop[i];
            organism->AddHealth(5);
            organism->AddHunger(5);
            MoveOrganism(i);
        }

        // b. Check for reproduction
        emp::vector<size_t> repro_schedule = emp::GetPermutation(random, GetSize());
        for (size_t i : repro_schedule) {
            if (IsOccupied(i)) {
                emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
                if (offspring) {
                    DoBirth(*offspring, i); // Add offspring at the parent's location
                }
            }
        }
    }

    emp::Ptr<Organism> ExtractOrganism(size_t location) {
        if (!IsOccupied(location)) return nullptr;
        emp::Ptr<Organism> organism = pop[location];
        pop[location] = nullptr;
        return organism;
    }

    void MoveOrganism(size_t old_location) {
        if (!IsOccupied(old_location)) return;
        emp::Ptr<Organism> organism = ExtractOrganism(old_location);
        if (organism) {
            emp::WorldPosition new_location = GetRandomNeighborPos(old_location);
            if (!IsOccupied(new_location)) {
                AddOrgAt(organism, new_location);
            } else {
                AddOrgAt(organism, old_location); // Put back if no move
            }
        }
    }
};

#endif