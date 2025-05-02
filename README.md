# Artificial Ecology - Crickets vs. Grass

## Overview
This project simulates an artificial ecological system where crickets and grass interact in a grid-based world. The simulation models the behavior of crickets (e.g., eating grass, reproducing) and grass (e.g., growing with weather conditions, reproducing) over time. The goal is to observe the balance between the two populations and how environmental factors influence their survival.

## Features
- **Crickets**:
  - Move randomly across the grid.
  - Eat grass if it is within their neighboring cells.
  - Reproduce when their health is high and hunger is low.
- **Grass**:
  - Grows based on weather conditions (rainy, cloudy, sunny).
  - Reproduces when it has sufficient health, water, and sunshine.
- **Weather Simulation**:
  - Randomly generated weather conditions affect the growth of grass and the behavior of crickets.
- **Visualization**:
  - A grid-based canvas displays the positions of crickets and grass in real-time.
  - Crickets are represented as brown squares, and grass as green squares.

## How It Works
1. **Initialization**:
   - The world is initialized as a 2D grid with a specified number of crickets and grass patches.
   - Each organism is placed randomly on the grid.

2. **Simulation Loop**:
   - The simulation runs in discrete time steps. During each step:
     - Weather conditions are updated.
     - Grass grows based on the weather.
     - Crickets move, eat grass, and reproduce.
     - Grass reproduces if conditions are met.

3. **Visualization**:
   - The grid is updated in real-time to reflect the current state of the world.

## Code Structure
- **`Organism.h`**:
  - Base class for all organisms in the simulation. Defines common properties like health and methods for processing state, eating, and reproduction.
- **`Grass.h`**:
  - Derived class representing grass. Includes properties for water and sunshine and logic for growth and reproduction.
- **`Cricket.h`**:
  - Derived class representing crickets. Includes properties for hunger and logic for eating grass, moving, and reproduction.
- **`World.h`**:
  - Manages the grid-based world and interactions between organisms (e.g., eating, reproduction).
- **`AEAnimate.cpp`**:
  - Handles the visualization and animation of the simulation using Empirical's web tools.

### Dependencies
- [Empirical Library](https://github.com/devosoft/Empirical)

### Author
Jared Arroyo Ruiz

### Acknowledgments
This project was developed as part of Anya E. Vostinar's Artificial Life and Digital Evolution course. It serves as an assignment focused on artificial ecologies, building upon foundational concepts and code from her Inheritence Lab nd Empirical World Lab. The implementation adapts and extends these ideas to create a dynamic simulation of crickets and grass interacting within a grid-based ecosystem.

Additionally, tools like GitHub Copilot and Gemini were utilized to assist in writing comments and formatting this README file, ensuring clarity and consistency throughout the documentation.