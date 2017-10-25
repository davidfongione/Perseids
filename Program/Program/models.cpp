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

void es_euler(const int years, std::string folder)
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

void ejs_verlet(const int years, std::string folder)
{
    
    //  verlet algorithm
    //  earth-jupiter-sun system
    //  the sun is the center of mass with a 0 velocity
    //  initial position of the Earth is (1, 0)
    //  initial position of Jupiter is (1.5237, 0)
    //  we vary the mass of Jupiter
    
    solver system;
    
    system.add(earth_calculated);
    system.add(jupiter_calculated);
    system.add(sun_mass_center);
    
    system.euler(years, folder);
}

void ejs_rmc_euler(const int years, std::string folder)
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

void ejs_rmc_verlet(const int years, std::string folder)
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

void fs_rmc_verlet(const int years, std::string folder)
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

void free_model(const int years, const std::string folder)
{
    
    solver system;
    
    system.add(earth_calculated);
    system.add(sun_mass_center);
    
    system.verlet(years, folder);
}


void escape(const int years, std::string folder)
{
    
    //  vitesse d'échappement : (0., 0.0243)
    
    planet terre("earth", 6.E24, 1., 0., 0., 0.03);
    solver system;
    system.add(terre);
    system.add(sun_mass_center);
    
    system.verlet(years, folder);
    
}








