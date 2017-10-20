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
    
    _prev_pos = other._prev_pos;
    _prev_vel = other._prev_vel;
    _prev_acc = other._prev_acc;
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

double solver::time(void) const
{
    
    return (_time);
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

void solver::add(planet body)
{
    
    _card++;
    
    _update_mass_center(body);
    _total_mass += body.mass();
    
    body.normalize();
    _system.push_back(body);
    //  only normalizes the mass and the velocity
    
    _prev_pos.push_back(body.position);
    _prev_vel.push_back(body.velocity);
    _prev_acc.push_back(_acceleration(_card - 1));
    //  the new planet is the (_card - 1) celestial body of the system
}

void solver::_update_mass_center(const planet& body)
{
    
    double total_mass;
    
    _mass_center[0] *= _total_mass;
    _mass_center[1] *= _total_mass;
    
    total_mass = _total_mass + body.mass();
    
    _mass_center[0] += body.mass() * body.position[0];
    _mass_center[1] += body.mass() * body.position[1];
    _mass_center[0] /= total_mass;
    _mass_center[1] /= total_mass;
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
    double mass;
    double r;
    vector<double> relative_pos(2);
    vector<double> acceleration(2);
    
    if(_system[p].distance_center() != 0.)
    {
        //  we don't need the calculation if the body is at the origin, like the sun
    
        r = _system[p].distance_center();
        radical = - 1. / (r*r*r);    //  avoid too many flops
        
        acceleration[0] = radical * _system[p].position[0];
        acceleration[1] = radical * _system[p].position[1];
    
        for(int k = 0; k < _card; k++)
        {
            if(k != p)
            {
                mass = _system[k].mass() / 2.E30;   //  normalize with the Sun's mass
                //  time/distance units are normalized with the constant 4*pi*pi
                r = _system[p].distance(_system[k]);
                radical = (mass) / (r*r*r);
                
                relative_pos[0] = _system[p].position[0] - _system[k].position[0];
                relative_pos[1] = _system[p].position[1] - _system[k].position[1];
                
                acceleration[0] -= radical * relative_pos[0];
                acceleration[1] -= radical * relative_pos[1];
            }
        }
        
        acceleration[0] *= g_const ;
        acceleration[1] *= g_const;
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
    double h;
    string folder;
    string path;
    ofstream output;
    
    h = ((double) years) / ((double) meshpoints);
    
    for(int i = 1; i < meshpoints; i++)
    {
        //  we go through each time-step and then through each planet
        for(int k = 0; k < _card; k++)
        {
            folder = "/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/euler/";
            path = folder + _system[k].name();
            
            if( i == 1)
            {
                output.open(path);  //  erase the previous file
                
                output << _system[k].name() << " (x, y, vx, vy)" << endl;
                output << "Timestep: " << years << endl << endl;
            }
            else
            {
                output.open(path, ios::app);   //  write after the existing content
            }
            
            _system[k].print_brut(output);
            
            _system[k].position[0] = h * _prev_vel[k][0] + _prev_pos[k][0];
            _system[k].position[1] = h * _prev_vel[k][1] + _prev_pos[k][1];
            
            _system[k].velocity[0] = h * _prev_acc[k][0] + _prev_vel[k][0];
            _system[k].velocity[1] = h * _prev_acc[k][1] + _prev_vel[k][1];
            
            output.close();
        }
        
        _update_quantities();
    }
    
    _time += years;
}

void solver::_update_quantities(void)
{
    
    for(int k = 0; k < _card; k++)
    {
        _prev_pos[k] = _system[k].position;
        _prev_vel[k] = _system[k].velocity;
        _prev_acc[k] = _acceleration(k);
    }
}

















