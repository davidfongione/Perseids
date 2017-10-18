//
//  planet.cpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//


#include <iostream>
#include "planet.hpp"
#include <cmath>
#include <vector>
#include <string>

using namespace std;

//  constructors

planet::planet(void)
{
    
    _name = "AUTO NAMING";
    
    _mass = 1.;
    _potential = 0.;
    _kinetic = 0.;
    
    position = {1., 0.};
    velocity = {0., 0.};

}

planet::planet(std::string name, double mass, double x, double y, double vx, double vy)
{
    
    _name = name;
    
    _mass = (double) mass;
    _potential = 0.;
    _kinetic = 0.;
    
    position = {x, y};
    velocity = {vx, vy};
}

planet::planet(const planet& other)
{
    
    _name = other._name + " copy";
    
    _mass = other._mass;
    _potential = other._potential;
    _kinetic = other._kinetic;
    
    position = other.position;
    velocity = other.velocity;
    
}

//  calculations

double planet::distance(const planet& other) const
{
    
    double sum = 0.;
    double aux_sum;
    
    for(int i = 0; i < 2; i++)
    {
        aux_sum = position[i] - other.position[i];
        sum += aux_sum * aux_sum;
    }
    
    return (sqrt(sum));
}

double planet::distance_center(void) const
{
    
    double sum = 0.;
    
    for(int i = 0; i < 2; i++)
    {
        sum += position[i] * position[i];
    }
    
    return (sqrt(sum));
}

double planet::grav_force(const planet& other) const
{
    
    double const g = 6.67408e-11;
    double force;
    
    force = (g * _mass * other._mass) / (distance(other) * distance(other));
    
    return (force);
}

std::string planet::name(void) const
{
    
    return (_name);
}


//  quantities

double planet::mass(void) const
{
    
    return (_mass);
}

//  energies

double planet::kinetic(void) const
{
    
    double energy = 0.;
    
    for(int i = 0; i < 2; i++)
    {
        energy += velocity[i] * velocity[i];
    }
    
    energy *= (0.5 * _mass);
    
    return (energy);
}

double planet::potential(const planet& other) const
{
    double g_const = 4 * M_PI * M_PI;
    double energy = (-g_const * _mass * other._mass) / distance(other);
    
    return (energy);
}

double planet::total(const planet& other) const
{
    
    double energy = kinetic() + potential(other);
    
    return (energy);
}







