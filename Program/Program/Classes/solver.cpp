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

std::vector<planet> solver::object(void) const
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

vector<double> solver::_eta(const int p) const
{
    
    //  p is the index of the planet for which we calculate eta
    
    double const mass = _system[p].mass();
    double const g_const = 4 * M_PI * M_PI;
    double r;
    double r_cube;
    vector<double> relative_pos;
    vector<double> eta;
    
    eta[0] = - (g_const * _system[p].position[0]) / _system[p].distance_center();
    eta[1] = - (g_const * _system[p].position[1]) / _system[p].distance_center();
    
    for(int k = 0; k < _card; k++)
    {
        //  cannot create an alias to the curent planet because of const

        if(_system[p].distance(_system[k]) != 0.)
        {
            relative_pos[0] = _system[p].position[0] - _system[k].position[0];
            relative_pos[1] = _system[p].position[1] - _system[k].position[1];
            r = _system[p].distance(_system[k]);
            r_cube = r*r*r;
            
            eta[0] -= (g_const * (_system[k].mass() / mass) * relative_pos[0]) / (r_cube);
            eta[1] -= (g_const * (_system[k].mass() / mass) * relative_pos[1]) / (r_cube);
        }
    }
    
    return (eta);
}

void solver::euler(const int time, const int meshpoints)
{
    
    double h = ((double) time - (double) _time) / meshpoints;
    vector<double> eta;
    planet* curent = nullptr;   //  alias to the curent planet
    ofstream output;
    string folder;
    string path;
    
    for(int k = 0; k < _card; k++)  //  go through every planet
    {
        curent = &_system[k];

        folder = "/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/euler/";
        path = folder + curent->name();
        output.open(path);
        
        curent->print_brut(output);
        
        for(int i = 1; i < meshpoints; i++)
        {
            eta = _eta(k);
            curent->position[0] = h * eta[0] + curent->velocity[0];
            curent->position[1] = h * eta[1] + curent->velocity[1];
            
            curent->velocity[0] = h * curent->velocity[0] + curent->position[0];
            curent->velocity[1] = h * curent->velocity[1] + curent->position[1];
            
            curent->print_brut(output);
        }
        
        output.close();
    }
}



















