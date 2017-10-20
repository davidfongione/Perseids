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
    _dim = 2;
    _mass = 1.;
    
    position = {1., 0.};
    velocity = {0., 0.};

}

planet::planet(std::string name, double mass, double x, double y, double vx, double vy)
{
    
    _name = name;
    
    _dim = 2;
    
    _mass = (double) mass;
    
    position = {x, y};
    velocity = {vx, vy};
}

planet::planet(const planet& other)
{
    
    _name = other._name + " copy";
    
    _mass = other._mass;
    
    position = other.position;
    velocity = other.velocity;
    
}

//  calculations

double planet::distance(const planet& other) const
{
    
    double sum = 0.;
    double aux_sum;
    
    
    
    for(int i = 0; i < _dim; i++)
    {
        aux_sum = position[i] - other.position[i];
        sum += aux_sum * aux_sum;
    }
    
    return (sqrt(sum));
}

double planet::distance_center(void) const
{
    
    double sum = 0.;
    
    
    
    for(int i = 0; i < _dim; i++)
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

int planet::dim(void) const
{
    
    return (_dim);
}

std::string planet::name(void) const
{
    
    return (_name);
}

void planet::print(std::ofstream& file) const
{
    
    file << _name << endl;
    file << _mass << "kg" << endl;
    
    file << "Position; " << endl;
    for(int i = 0; i < _dim; i++)
    {
        file << position[i] << endl;
    }
    file << "Velocity; " << endl;
    for(int i = 0; i < _dim; i++)
    {
        file << velocity[i] << endl;
    }
    
    file << endl;
    
}


//  quantities

double planet::mass(void) const
{
    
    return (_mass);
}

//  energies

double planet::kinetic_energy(void) const
{
    
    double energy = 0.;
    
    for(int i = 0; i < _dim; i++)
    {
        energy += velocity[i] * velocity[i];
    }
    
    energy *= (0.5 * _mass);
    
    return (energy);
}

double planet::potential_energy(const std::vector<planet>& system) const
{
    
    double energy = 0.;
    double r;
    double g_const = 4 * M_PI * M_PI;
    
    for(auto& planet : system)
    {
        if(distance(planet) != 0.)
        {
            r = distance(planet);
            energy += (_mass * planet._mass) / (r*r);
        }
    }
    
    energy *= g_const;
    
    return (energy);
}

double planet::total_energy(const std::vector<planet>& system) const
{
    
    double energy = kinetic_energy() + potential_energy(system);
    
    return (energy);
}







