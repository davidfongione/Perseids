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
#include <array>

using namespace std;

//  constructors

planet::planet(void)
{
    
    _mass = 1.;
    _potential = 0.;
    _kinetic = 0.;
    
    _position[0] = 1.;
    _position[1] = 0.;
    _velocity[0] = 0.;
    _velocity[1] = 0.;

}

planet::planet(double mass, double x, double y, double vx, double vy)
{
    
    _mass = (double) mass;
    _potential = 0.;
    _kinetic = 0.;
    
    _position[0] = (double) x;
    _position[1] = (double) y;
    _velocity[0] = (double) vx;
    _velocity[1] = (double) vy;
}

planet::planet(const planet& other)
{
    
    _mass = other._mass;
    _potential = other._potential;
    _kinetic = other._kinetic;
    
    _position[0] = other._position[0];
    _position[1] = other._position[1];
    _velocity[0] = other._velocity[0];
    _velocity[1] = other._velocity[1];
    
}

//  calculations

double planet::distance_to(const planet& other) const
{
    
    double sum = 0.;
    double product = 0.;
    
    for(int i = 0; i < 2; i++)
    {
        product = _position[0] - other._position[1];
        sum += product * product;
    }
    
    return (sqrt(product));
}

double planet::grav_force(const planet& other) const
{
    
    double const g = 6.67408e-11;
    double force;
    
    force = (g * _mass * other._mass) / (distance_to(other) * distance_to(other));
    
    return (force);
}

//  quantities

double planet::mass(void) const
{
    
    return (_mass);
}

array<double, 2> planet::position(void) const
{
    
    return (_position);
}

array<double, 2> planet::position(const planet& other) const
{
    
    array<double, 2> position;
    
    for(int i = 0; i < 2; i++)
    {
        position[i] = _position[i] - other._position[i];
    }
    
    return (position);
}

array<double, 2> planet::velocity(void) const
{
    
    return (_velocity);
}

array<double, 2> planet::velocity(const planet& other) const
{
    
    array<double, 2> velocity;
    
    for(int i = 0; i < 2; i++)
    {
        velocity[i] = _velocity[i] - other._velocity[i];
    }
    
    return (velocity);
}

//  energies

double planet::kinetic_enery(void) const
{
    
    double v_squared = 0.;
    
    for(int i = 0; i < 2; i++)
    {
        v_squared += _velocity[i] * _velocity[i];
    }
    
    return (0.5 * _mass * v_squared);
}

double planet::potential_energy(const planet& other) const
{
    double g_const = 4 * M_PI * M_PI;
    double energy = (-g_const * _mass * other._mass) / distance_to(other);
    
    return (energy);
}

double planet::total_energy(const planet& other) const
{
    
    double energy = kinetic_enery() + potential_energy(other);
    
    return (energy);
}







