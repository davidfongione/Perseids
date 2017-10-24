# Perseids <br> Project 3 from the course FYS3150 of University of Oslo, Autumn 2017


The goal of this project is to compute a simulation of the Solar System with both Euler's and Verlet's algorithms to solve the ordinary differential equations combined with Newton's law.

## Implementation

The program is object oriented and uses two classes :
- `planet` which encapsulated the fundamental data of a celestial body such as its position, velocity, mass and its energies
- `solver` which basically is a vector of planets and on which we compute operations such as the center of mass, the energies of the full system, and of course the position, velocity and acceleration of each planet with **Euler's** or **Verlet's** algorithm.

### Planet class

You can declare a new planet with its position and velocity vectors as `planet body("name", x, y, vx, vy);`. The time will be initialized at *t=0* :

```cpp
#include "planet.hpp"

planet earth("earth", 6.E24, 8.30757514E-01, 5.54644964E-01, -9.79193739E-03, 1.42820162E-02);
planet sun("sun", 2.E30, 2.17112305E-03, 5.78452455E-03, -5.30635989E-06, 5.44444408E-06);
```

Several useful methods can be found in the [header file](https://github.com/kryzar/Perseids/blob/master/Program/Program/classes/solver.hpp) and used very easily. You can print the last position and velocity of a planet to a file by simply :

```cpp

std::ofstream output;
earth.print(output);
```

or add the energies if you want (they depend on the other planets in the system):

```cpp

std::ofstream output;
vector<planet> system;

//  suppose we add planets and that earth is in this system

earth.print(output, system);
```

All the initial conditions for our planets of the Solar System can be found on this very useful NASA website.


### Solver class
