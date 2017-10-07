//
//  planet.cpp
//  Program
//
//  Created by Antoine Hugounet on 06/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//


#include "planet.hpp"
#include <cmath>


//  constructors

planet::planet(void)
{
    _mass = 1.;
    
    _position[0] = 1.;
    _position[1] = 0.;
    
    _velocity[0] = 0.;
    _velocity[1] = 0.;
}

planet::planet(double mass, double x, double y, double vx, double vy)
{
    _mass = mass;
    
    _position[0] = (double) x;
    _position[1] = (double) y;
    
    _velocity[0] = (double) vx;
    _velocity[1] = (double) vy;
}


//  methods

double planet::distance(const planet other_planet)
{
    double sum = 0.;
    double temp;
    
    for(int i = 0; i < 2; i++)
    {
        temp = (_position[i] - other_planet._position[i]);
        sum += temp * temp;
    }
    
    return sqrt(sum);
}
