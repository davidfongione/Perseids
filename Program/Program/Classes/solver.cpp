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

void solver::print(ofstream& file, const int dim) const
{
    file << "=== SOLAR SYSTEM === " << endl;
    
    for(int p = 0; p < _card ; p++)
    {
        file << _system[p].name() << endl;
        file << _system[p].mass() << "kg" << endl;
        file << "Kinetic energy: " << _system[p].kinetic() << endl;
        // file << "Potential energy: " << _system[p].potential() << endl;
        
        file << "Position; " << endl;
        for(int i = 0; i < dim; i++)
        {
            file << _system[p].position[0] << endl;
            file << _system[p].position[1] << endl;
        }
        file << "Velocity; " << endl;
        for(int i = 0; i < dim; i++)
        {
            file << _system[p].velocity[0] << endl;
            file << _system[p].velocity[1] << endl;
        }
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

vector<double> solver::_eta(const vector<planet>& system, const double*** sys_pos, const int p, const int i) const
{
    
    //  p is the index of the planet for which we calculate eta
    //  i is the index of the current meshpoint
    
    double const mass = system[p].mass();
    double const g_const = 4 * M_PI * M_PI;
    double const x = _sys_pos[p][i][0];
    double const y = _sys_pos[p][i][1];
    //  position of the p planet at the meshpoint i
    //  0 stands for x and 1 for y
    double r;
    double r_cube;

    vector<double> relative_pos;
    vector<double> eta;
    
    eta[0] = - (g_const * x) / system[p].distance_center();
    eta[1] = - (g_const * y) / system[p].distance_center();
    
    for(int k = 0; k < _card; k++)
    {
        relative_pos[0] = x - _sys_pos[k][i][0];
        relative_pos[1] = y - _sys_pos[k][i][1];
        r = system[p].distance(system[k]);
        r_cube = r*r*r;
        
        if(r != 0)
        {
            eta[0] -= (g_const * (system[k].mass() / mass) * relative_pos[0]) / (r_cube);
            eta[1] -= (g_const * (system[k].mass() / mass) * relative_pos[1]) / (r_cube);
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

