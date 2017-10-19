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

using namespace std;

//  constructor

solver::solver(void)
{
    
    _sys_pos = nullptr;
    _sys_vel = nullptr;
}


//  destructor

solver::~solver()
{
    
    for(int p = 0; p < _card; p++)
    {
        
        for(int i = 0; i < _meshpoints; i++)
        {
            delete[] _sys_pos[_card][_meshpoints];
            delete[] _sys_vel[_card][_meshpoints];
        }
        
        delete[] _sys_pos[_card];
        delete[] _sys_vel[_card];
    }
    
    delete[] _sys_pos;
    delete[] _sys_vel;
}


//  methods

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
    _system.push_back(other);
}

vector<double> solver::mass_center(void) const
{
    
    double x;
    double y;
    vector<double> position;
    
    for(int p = 0; p < _card; p++)
    {
        x = _system[p].position[0];
        y = _system[p].position[1];
        
        position[0] += _system[p].mass() * x;
        position[1] += _system[p].mass() * y;
    }
    
    position[0] /= _total_mass();
    position[1] /= _total_mass();
    
    return (position);
}

//  utilities methods

vector<double> solver::_eta(const double*** sys_pos, const int p, const int i) const
{
    
    //  p is the index of the planet for which we calculate eta
    //  i is the index of the current meshpoint
    
    double const mass = _system[p].mass();
    double const g_const = 4 * M_PI * M_PI;
    double const x = _sys_pos[p][i][0];
    double const y = _sys_pos[p][i][1];
    //  position of the p planet at the meshpoint i
    //  0 stands for x and 1 for y
    double r;

    vector<double> relative_pos;
    vector<double> eta;
    
    eta[0] = - (g_const * x) / _system[p].distance_center();
    eta[1] = - (g_const * y) / _system[p].distance_center();
    
    for(int k = 0; k < _card; k++)
    {
        
        if(_system[p].distance(_system[k]) != 0.)
        {
            relative_pos[0] = x - _sys_pos[k][i][0];
            relative_pos[1] = y - _sys_pos[k][i][1];
            r = _system[p].distance(_system[k]);
            
            eta[0] -= (g_const * (_system[k].mass() / mass) * relative_pos[0]) / (r*r*r);
            eta[1] -= (g_const * (_system[k].mass() / mass) * relative_pos[1]) / (r*r*r);
        }
    }
    
    return (eta);
}

double solver::_total_mass(void) const
{
    
    double mass = 0.;
    
    for(int p = 0; p < _card ; p++)
    {
        mass += _system[p].mass();
    }
    
    return (mass);
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
