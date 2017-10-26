# The Verlet Underground <br> Project 3 from the course FYS3150 of University of Oslo, Autumn 2017


This program aims to compute a simulation of the Solar System with both Euler's and Verlet's algorithms to solve the ordinary differential equations of the system combined with Newton's law.

[![The orbits of the planets in the Solar System for the next 30 years](https://s1.postimg.org/9kfx39w6lr/plot.png)](https://postimg.org/image/4xua2kxmy3/)

## Implementation

The program is object oriented and uses two classes :
- `planet` which encapsulated the fundamental data of a celestial body such as its position, velocity, mass and its energies
- `solver` which basically is a vector of planets and on which we compute operations such as the center of mass, the energies of the full system, and of course the position, velocity and acceleration of each planet with **Euler's** or **Verlet's** algorithm

### Planet class

You can declare a new planet with its position and velocity vector components by `planet body("name", x, y, vx, vy);`. The time will be initialized at *t=0* :

```cpp
#include "planet.hpp"

planet earth("earth", 6.E24, 8.30757514E-01, 5.54644964E-01, -9.79193739E-03, 1.42820162E-02);
planet sun("sun", 2.E30, 2.17112305E-03, 5.78452455E-03, -5.30635989E-06, 5.44444408E-06);
```

Several useful methods can be found in the [header file](https://github.com/kryzar/Perseids/blob/master/Program/Program/classes/solver.hpp) and used very easily. For example, you can print the last position and velocity of a planet to an `ofstream` by simply :

```cpp
earth.print(output);
```

or add the energies if you want (they depend on the other planets in the system):

```cpp
vector<planet> system;
//  suppose we add planets and that earth is in this system
earth.print(output, system);
```

All the initial conditions for the celestial bodies of the Solar System can be found on this [very useful NASA website](https://ssd.jpl.nasa.gov/horizons.cgi#top), just select **VECTORS** as an *ephemeris type*. You must initialize the mass in *kg*, the position in *AU*, and the velocity in *AU/day*.


### Solver class
#### Basic run of a solar system

This class is the one that compute all the calculations. Here is a basic example on how it works :

```cpp

#include "planet.hpp"
#include "solver.hpp"
#include "initialisations.hpp"  //  declarations of the planets as we seen above
#include <string>


int main()
{

  solver system; // create a solar system
  std::string folder;  // path to the folder in which you want the data files

  folder = "desktop/output files/";

  //  add planets

  system.add(earth);
  system.add(jupiter);
  system.add(mars);
  system.add(mercury);
  system.add(neptune);
  system.add(saturn);
  system.add(sun);
  system.add(venus);
  system.add(uranus);

  //  run the verlet algorithm for the next 12 years

  system.verlet(12., folder);

  //  print the energies

  std::cout << system.kinetic_energy() << std::endl;
  std::cout << system.potential_energy() << std::endl;
  std::cout << system.total_energy() << std::endl;

  //  and so forth

  return 0;
}

```

The algorithm requires only a time-period (in years) - `12.` here - and a folder path - `folder` here - to output the data files. It automatically generate 365 time-steps per year and it is the same for `euler`.
However it is possible to compute the same algorithm enhanced with a relativistic correction of Newton's law. The resolution is enhanced to one arcsecond and therefore the program requires a long time to run. The output file contains only a fraction of all the computed positions and velocities : it is reliable enough for a good plot (you won't notice the difference between a relativistic and not relativistic plot), saves time, and only the last position if required to calculate a perihelion precession. If you with to add this correction, just use a boolean in `verlet`(Euler is not efficient enough for this simulation) :

```cpp

system.verlet(100., folder, true);  //  with correction
system.verlet(100., folder, false); //  without
system.verlet(100., folder);        //  without, exactly the same

```

1. Note that the Sun **must** be considered as any other planet as it is not the center of mass of the Solar System, and therefore has a non-zero position and velocity. Its motion is very small however
2. `folder` must finish by a `/`so the program creates data files exactly where you want and this folder must already exist, otherwise the program won't be able to create the data files
3. It is equivalent to run with `false`or nothing.

The declaration and initializations of the planets of the Solar System are given in [`initialisations.hpp`](https://github.com/kryzar/Perseids/blob/master/Program/Program/initialisations.hpp). You can find initializations for the full solar system, the Earth-Jupiter-Sun system with the Sun as the center of mass and the Earth-Jupiter-Sun with the real center of mass.



#### Output files

Once you gave the program a `folder`, it will automatically create many small data files :

1. One text file for each planet automatically named by the planet's name containing the position and velocity at each time-step of the discretization
2. Those files can be used by [Gnuplot](http://gnuplot.sourceforge.net) and therefore the program also creates two Gnuplot scripts to be ran in the teminal : *plot.gnu* which makes a simple plot in the terminal and *plot-png.gnu* which creates a png image of the system in the same folder
3. The program also creates a file *system-total-energy* which - as for the position and velocity of each planet - gives the total energy of the system at each time-step. This file can also be used by Gnuplot but no script is generated (for the moment)

[![Example of the program ran above](https://s1.postimg.org/3u7luzcw4v/Capture_d_cran_2017-10-24_18.54.12.jpg)](https://postimg.org/image/1rrt6xeb3f/)

Other possibilities can be found in the [header file](https://github.com/kryzar/Perseids/blob/master/Program/Program/classes/solver.hpp) of this class.

## Warning

Several approximations have been made to compute this simulation, mainly due to lack of time. But :
1. The orbits are supposed to be circular instead of elliptical
2. We only computed 2-dimensions vectors, assuming the orbits are nearly coplanar, but it is wrong in the reality
3. We neglected the effects of the general relativity. They are very subtle but can be seen for Mercury for long periods of time
4. The loss of numerical precision is an important issue for the energies. For example, the total energy of the Earth-system should be `899574073760227393536.0` given initial conditions, and the program outputs `899574073760227655680.0`, which is a difference of nearly six orders of magnitude. To be corrected

## License

Do whatever you want with those files, especially if you wish to improve them. I did this program as a beginner programmer so there must be A LOT to improve. There is no official license (again because I don't have time to read everything) but I don't think that it will be a problem.
