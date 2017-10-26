//
//  models.cpp
//  Program
//
//  Created by Antoine Hugounet on 23/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//


#include "classes/planet.hpp"
#include "classes/solver.hpp"
#include "initialisations.hpp"
#include <string>
#include "time.h"
#include <iostream>

//  es = earth-sun
//  ejs = earth-jupiter-sun
//  rmc = real mass center
//  fs = full system

void es_euler(const double years, std::string folder)
{
    
    //  euler algorithm
    //  earth-sun system
    //  the sun is the center of mass and with a zero velocity
    //  initial position of the Earth is (1, 0)
    
    solver system;
    
    system.add(earth_calculated);
    system.add(sun_mass_center);
    
    system.euler(years, folder);
}

void ejs_verlet(const double years, std::string folder)
{
    
    //  verlet algorithm
    //  earth-jupiter-sun system
    //  the sun is the center of mass with a 0 velocity
    //  initial position of the Earth is (0., 1.)
    //  initial position of Jupiter is (0., 5.20)
    //  the velocity vector is (0, 2*pi*R / T), R being the radius and T the revolution period
    //  we vary the mass of Jupiter
    
    solver system;
    
    system.add(earth_calculated);
    system.add(jupiter_calculated);
    system.add(sun_mass_center);
    
    system.verlet(years, folder);
}

void ejs_rmc_euler(const double years, std::string folder)
{
    
    //  euler algorithm (to compare)
    //  earth-jupiter-sun system
    //  we use the real mass center of the system and so the nasa data
    //  as a consequence the sun is considered as any other body in the system
    
    solver system;
    
    system.add(earth);
    system.add(jupiter);
    system.add(sun);
    
    system.euler(years, folder);
}

void ejs_rmc_verlet(const double years, std::string folder)
{
    
    //  verlet algorithm
    //  earth-jupiter-sun system
    //  we use the real mass center of the system and so the nasa data
    //  as a consequence the sun is considered as any other body in the system
    
    solver system;
    
    system.add(earth);
    system.add(jupiter);
    system.add(sun);
    
    system.verlet(years, folder);
}

void fs_rmc_verlet(const double years, std::string folder)
{
    
    //  verlet algorithm
    //  full solar system
    //  we use the real mass center of the system and so the nasa data
    
    solver system;
    
    system.add(earth);
    system.add(jupiter);
    system.add(mars);
    system.add(mercury);
    system.add(neptune);
    system.add(saturn);
    system.add(sun_calculated);
    system.add(venus);
    system.add(uranus);
    
    system.verlet(years, folder);
}

void free_model(const double years, const std::string folder)
{
    
    solver system;
    
    system.add(earth_calculated);
    system.add(sun_mass_center);
    
    system.verlet(years, folder);
}


void escape(const double years, std::string folder)
{
    
    //  vitesse circulaire : (0., 0.0172)
    //  vitesse d'échappement : (0., 0.0243)
    
    planet terre("earth", 6.E24, 1., 0., 0., 0.012);
    solver system;
    system.add(terre);
    system.add(sun_mass_center);
    
    system.verlet(years, folder);
    
}








