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

    std::string GetWeather() {

        if (weather < 0.5) { //rainy, we are in seattle
            
            return "Rainy";
        } 

        else if (weather < 0.85) { //cloud

            return "Cloudy";
        }

        return "Sunny";
    }

    void Update() {

        // First, let the base World class handle its updates
        emp::World<Organism>::Update();

        double current_weather = UpdateWeather();

        emp::vector<size_t> weather_schedule = emp::GetPermutation(random, GetSize());
    
            for (int i : weather_schedule) {
    
                if (!IsOccupied(i)) {
    
                    continue; 
                }
                
                emp::Ptr<Organism> organism = ExtractOrganism(i);
                organism->Process(current_weather);

                if (organism->GetType() == "Cricket") {

                    emp::WorldPosition randNeighborPos = GetRandomNeighborPos(i);
                    AddOrgAt(organism, randNeighborPos);

                } else {

                    AddOrgAt(organism, i);
                } 
            }

        emp::vector<size_t> eat_schedule = emp::GetPermutation(random, GetSize());

        for (int i : eat_schedule) {

            if (!IsOccupied(i)) {

                continue; 
            }
            
            emp::Ptr<Organism> organism = pop[i]; // Do not extract the organism here

            if (organism->GetType() == "Cricket") {

                emp::vector<size_t> neighbors = GetValidNeighborOrgIDs(i);

                for (int neighborIndex : neighbors) {

                    if (pop[neighborIndex]) {

                        emp::Ptr<Organism> neighbor = ExtractOrganism(neighborIndex); // Do not extract the neighbor
                        organism->Eat(neighbor);
                        
                    }
                }
            }
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