//
//  planet.hpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//


#pragma once
#include <array>

using namespace std;



class planet
{
public:
    planet(void);
    planet(double mass, double x, double y, double vx, double vy);
    planet(const planet& other);    //  probably useless but more secure to prevent C++'s bad behaviors
    
    //  calculations
    double distance_to(const planet& other) const;
    double grav_force(const planet& other) const;
    
    //  quantities
    double mass(void) const;
    array<double, 2> position(void) const;
    array<double, 2> position(const planet& other) const;    //  position with respect to the other planet
    array<double, 2> velocity(void) const;
    array<double, 2> velocity(const planet& other) const;    //  velocity with respect to the other planet
    
    //  energies
    double kinetic_enery(void) const;
    double potential_energy(const planet& other) const;
    double total_energy(const planet& other) const;
    
private:
    double _mass;
    double _potential;
    double _kinetic;
    
    array<double, 2> _position;    //  we use this class to return array functions
    array<double, 2> _velocity;
};
