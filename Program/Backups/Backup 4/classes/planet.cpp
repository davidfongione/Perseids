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

    time = 0;
    _name = "AUTO NAMING";
    _dim = 2;
    _mass = 1.;

    position = {1., 0.};
    velocity = {0., 0.};
}

////////

planet::planet(std::string name, double mass, double x, double y, double vx, double vy)
{

    time = 0;
    _name = name;
    _dim = 2;
    _mass = (double) mass;

    position = {x, y};
    velocity = {vx, vy};

    time = 0;
}

////////

planet::planet(const planet& body)
{

    time = body.time;
    _name = body._name;
    _dim = body._dim;
    _mass = body._mass;

    position = body.position;
    velocity = body.velocity;

}

//  getters

int planet::dim(void) const
{

    return (_dim);
}

////////

double planet::mass(void) const
{

    return (_mass);
}

////////

std::string planet::name(void) const
{

    return (_name);
}

//  methods

double planet::distance(const planet& body) const
{

    double sum = 0.;
    double relative_position;

    for(int i = 0; i < _dim; i++)
    {
        relative_position = position[i] - body.position[i];
        sum += relative_position * relative_position;
    }

    return (sqrt(sum));
}

////////

double planet::distance_center(void) const
{

    double sum = 0.;

    for(int i = 0; i < _dim; i++)
    {
        sum += position[i] * position[i];
    }

    return (sqrt(sum));
}

////////

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

////////

double planet::potential_energy(const planet& body) const
{
    
    double energy;
    
    if(distance(body) != 0.)
    {
        double r = distance(body);
        
        energy = (4 * M_PI * M_PI * _mass * body._mass) / (r*r);
    }
    else
    {
        energy = 0.;
    }
    
    return (energy);
}

////////

double planet::potential_energy(const std::vector<planet>& system) const
{

    double energy = 0.;

    for(auto& body : system)
    {
        energy += potential_energy(body);
    }

    return (energy);
}

////////

double planet::total_energy(const planet& body) const
{
    
    double energy = kinetic_energy() + potential_energy(body);
    
    return (energy);
}

////////

double planet::total_energy(const std::vector<planet>& system) const
{

    double energy = kinetic_energy() + potential_energy(system);

    return (energy);
}

////////

void planet::normalize(void)
{
    _mass /= 2.E30;
    velocity[0] *= 365.25;
    velocity[1] *= 365.25;
}

////////

void planet::print(std::ofstream& output) const
{

    output << _name << endl;
    output << _mass << "kg" << endl;
    output << "At t=" << time << " years" << endl;

    output << "Position: " << endl;
    for(int i = 0; i < _dim; i++)
    {
        output << position[i] << endl;
    }
    output << "Velocity: " << endl;
    for(int i = 0; i < _dim; i++)
    {
        output << velocity[i] << endl;
    }

    output << endl;

}

////////

void planet::print(std::ofstream& output, const std::vector<planet>& system) const
{

    output << _name << endl;
    output << _mass << "kg" << endl;
    output << "At t=" << time << " years" << endl;
    output << "Kinetic energy: " << kinetic_energy() << endl;
    output << "Potential energy: " << potential_energy(system) << endl;
    output << "Total energy: " << total_energy(system) << endl;

    output << "Position: " << endl;
    for(int i = 0; i < _dim; i++)
    {
        output << position[i] << endl;
    }
    output << "Velocity: " << endl;
    for(int i = 0; i < _dim; i++)
    {
        output << velocity[i] << endl;
    }

    output << endl;

}

////////

void planet::print_pos(std::ofstream& output) const
{

    string space = "        ";

    for(int i = 0; i < _dim; i++)
    {
        output << position[i] << space;
    }
}

////////

void planet::print_vel(std::ofstream& output) const
{

    string space = "        ";

    for(int i = 0; i < _dim; i++)
    {
        output << velocity[i] << space;
    }
}
