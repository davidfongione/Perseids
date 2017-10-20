//
//  solver.cpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//


#include "solver.hpp"
#include "planet.hpp"
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

//  constructor

solver::solver(void)
{
    
    _card = 0;
    _time = 0;
    _total_mass = 0.;
    _mass_center = {0., 0.};
    
}

solver::solver(const solver& other)
{
 
    _card = other._card;
    _time = other._time;
    _total_mass = other._total_mass;
    _mass_center = other._mass_center;
    _system = other._system;
    
}

//  methods

int solver::size(void) const
{
    
    return (_card);
}

double solver::total_mass(void) const
{
    
    return (_total_mass);
}

void solver::print(ofstream& file) const
{
    
    file << "=== SOLAR SYSTEM === " << endl;
        
    for(int p = 0; p < _card ; p++)
    {
        _system[p].print(file);
    }
    
    file << "===/ SOLAR SYSTEM === " << endl;
}

void solver::add(const planet& other)
{
    
    _card++;
    _total_mass += other.mass();
    _system.push_back(other);
    _mass_center[0] +=  (other.mass() * other.position[0]) / _total_mass;
    _mass_center[1] +=  (other.mass() * other.position[1]) / _total_mass;
}

vector<double> solver::mass_center(void) const
{
    
    return (_mass_center);
}

//  utilities methods

std::vector<planet> solver::system(void) const
{
    
    return (_system);
}

double solver::kinetic_energy(void) const
{
    
    double energy = 0.;
    
    for(auto& object : _system)
    {
        energy += object.kinetic_energy();
    }
    
    return (energy);
}

double solver::potential_energy(void) const
{
    
    double energy = 0.;
    
    for(auto& object : _system)
    {
        energy += object.potential_energy(_system);
    }
    
    return (energy);
}

double solver::total_energy(void) const
{
    
    double energy = 0.;
    
    for(auto& object : _system)
    {
        energy += object.total_energy(_system);
    }
    
    return (energy);
}

vector<double> solver::_acceleration(const int p) const
{
    
    //  p is the index of the planet for which we calculate eta
    
    double const g_const = 4 * M_PI * M_PI;
    double radical;
    double relative_mass;
    double r;
    double r_squared;
    vector<double> relative_pos(2);
    vector<double> acceleration(2);
    
    if(_system[p].distance_center() != 0.)
    {
        //  we don't need the calculation if the body is at the origin, like the sun
    
        r = _system[p].distance_center();
        r_squared = r*r;
        radical = - g_const / r_squared;    //  avoid too many flops
        
        acceleration[0] = radical * _system[p].position[0];
        acceleration[1] = radical * _system[p].position[1];
    

        for(int k = 0; k < _card; k++)
        {
            if(k != p)
            {
                relative_mass = _system[k].mass() / _system[p].mass();
                r = _system[p].distance(_system[k]);
                radical = g_const * (relative_mass) / (r*r*r);
                
                relative_pos[0] = _system[p].position[0] - _system[k].position[0];
                relative_pos[1] = _system[p].position[1] - _system[k].position[1];
                
                acceleration[0] -= radical * relative_pos[0];
                acceleration[1] -= radical * relative_pos[1];
            }
        }
    }
    else
    {
        relative_pos[0] = 0.;
        relative_pos[1] = 0.;
    }
    
    return (acceleration);
}

void solver::euler(const double years, const int meshpoints)
{
    
    double h = ((double) years - (double) _time) / meshpoints;
    vector<double> acceleration(2);
    planet* curent = nullptr;   //  alias to the curent planet
    ofstream output;
    string folder;
    string path;
    string space = "        ";
    
    for(int k = 0; k < _card; k++)  //  go through every planet
    {
        curent = &_system[k];

        folder = "/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/euler/";
        path = folder + curent->name();
        output.open(path);
        output << curent->name() << " (x, y, vx, vy)" << endl << endl;
        curent->print_brut(output);
        
        for(int i = 1; i < meshpoints; i++)
        {
            acceleration = _acceleration(k);
            curent->position[0] = h * acceleration[0] + curent->velocity[0];
            curent->position[1] = h * acceleration[1] + curent->velocity[1];
            
            curent->velocity[0] = h * curent->velocity[0] + curent->position[0];
            curent->velocity[1] = h * curent->velocity[1] + curent->position[1];
            
            curent->print_brut(output);
        }
        
        output.close();
    }
}



















