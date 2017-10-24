# Perseids <br> Project 3 from the course FYS3150 of University of Oslo, Autumn 2017


The goal of this project is to compute a simulation of the Solar System with both Euler's and Verlet's algorithms to solve the ordinary differential equations combined with Newton's law.

## Implementation

The program is object oriented and uses two classes :
- `planet` which encapsulated the fundamental data of a celestial body such as its position, velocity, mass and its energies
- `solver` which basically is a vector of planets and on which we compute operations such as the center of mass, the energies of the full system, and of course the position, velocity and acceleration of each planet with *Euler's* or *Verlet's* algorithm.
