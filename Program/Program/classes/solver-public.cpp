//
//  solver-public.cpp
//  Program
//
//  Created by Antoine Hugounet on 8/10/2017.
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


//  constructors


solver::solver(void)
{
    
    _card = 0;
    _time = 0;
    _total_mass = 0.;
    _mass_center = {0., 0.};

}

////////

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


//  main algorithms


void solver::euler(const double years, const std::string folder)
{
    //  equations in 1D :
    //  x(t+dt) = dt*v(t) + x(t)
    //  v(t+dt) = dt*a(t) + v(t) = dt*Fx/m + v(t), with Newton's law
    
    int meshpoints;
    double h;
    // string folder;
    string path;
    ofstream output;
    
    meshpoints = (int) years * 365;
    
    h = ((double) years) / ((double) meshpoints);
    
    for(int i = 0; i <= meshpoints; i++)
    {
        for(int k = 0; k < _card; k++)
        {
            path = folder + _system[k].name();
            
            if( i == 1)
            {
                output.open(path);  //  erase the previous file
                output << "Euler algorithm (2D)" << endl;
                output << _system[k].name() << " (x, y, vx, vy)" << endl;
                output << "Timestep: " << years << " years" << endl << endl;
            }
            else
            {
                output.open(path, ios::app);   //  write after the existing content
            }
            
            _system[k].print_pos(output);   //  prints quantities for a gnuplot
            _system[k].print_vel(output);
            output << endl;
            
            _system[k].position[0] = h * _prev_vel[k][0] + _prev_pos[k][0];
            _system[k].position[1] = h * _prev_vel[k][1] + _prev_pos[k][1];
            
            _system[k].velocity[0] = h * _prev_acc[k][0] + _prev_vel[k][0];
            _system[k].velocity[1] = h * _prev_acc[k][1] + _prev_vel[k][1];
            
            _system[k].time += h;   //  update time
            output.close();
        }
        
        _print_total_energy(folder, i);
        _update_quantities(i, h);
    }
    
    _gnuplot(folder, years);
    _gnuplot_png(folder, years);
    
    _time += years;
}

////////

void solver::verlet(const double years, const std::string folder)
{
    //  equations in 1D :
    //  x(t+dt) = x(t) + dt*v(t) + (1/2)(dt^2)*a(t)
    //  v(t+dt) = v(t) + (1/2)*dt*[a(t) + a(t+dt)]
    
    int meshpoints;
    double h;
    double h_squared;
    double radical;
    string path;
    ofstream output;
    vector<vector<double>> next_acc;   //  vector for a(t+dt)
    
    meshpoints = (int) years * 365;
    h = ((double) years) / ((double) meshpoints);
    h_squared = h * h;
    
    for(int i = 1; i <= meshpoints; i++)
    {
        for(int k = 0; k < _card; k++)
        {
            path = folder + _system[k].name();
            
            if( i == 1)
            {
                output.open(path);  //  erase the previous file
                output << "Velocity-Verlet algorithm (2D)" << endl;
                output << _system[k].name() << " (x, y, vx, vy)" << endl;
                output << "Timestep: " << years << " years" << endl << endl;
            }
            else
            {
                output.open(path, ios::app);   //  write after the existing content
            }
            
            _system[k].print_pos(output);
            
            radical = 0.5 * h_squared;
            
            _system[k].position[0] = _prev_pos[k][0] + h * _prev_vel[k][0] + radical * _prev_acc[k][0];
            _system[k].position[1] = _prev_pos[k][1] + h * _prev_vel[k][1] + radical * _prev_acc[k][1];
            
            output.close();
        }
        
        next_acc = _next_acc();
        
        for(int k = 0; k < _card; k++)
        {
            path = folder + _system[k].name();
            output.open(path, ios::app);
            
            _system[k].print_vel(output);
            output << endl;
            
            radical = 0.5 * h;
            
            _system[k].velocity[0] = _prev_vel[k][0] + radical * (_prev_acc[k][0] + next_acc[k][0]);
            _system[k].velocity[1] = _prev_vel[k][1] + radical * (_prev_acc[k][1] + next_acc[k][1]);
            
            output.close();
        }
        
        _print_total_energy(folder, i);
        _update_quantities(i, h);
    }
    
    _gnuplot(folder, years);
    _gnuplot_png(folder, years);
}


//  getters


int solver::size(void) const
{
    
    return (_card);
}

////////

double solver::total_mass(void) const
{
    
    return (_total_mass);
}

////////

double solver::time(void) const
{
    
    return (_time);
}


//  methods


double solver::kinetic_energy(void) const
{
    
    double energy = 0.;
    planet copy;
    
    for(auto& body : _system)
    {
        copy = body;
        copy.denormalize(); //  avoid (a bit) loss of num. precision
        energy += copy.kinetic_energy();
    }
    
    return (energy);
}

////////

double solver::potential_energy(void) const
{
    
    double energy = 0.;
    planet copy;
    
    for(auto& body : _system)
    {
        copy = body;
        copy.denormalize();  //  avoid (a bit) loss of num. precision
        energy += copy.potential_energy(_system);
    }
    
    return (energy);
}

////////

double solver::total_energy(void) const
{
    
    double energy = kinetic_energy() + potential_energy();
    
    return (energy);
}

////////

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

////////

void solver::print(ofstream& file) const
{
    
    file << "=== SOLAR SYSTEM === " << endl;
    
    for(int p = 0; p < _card ; p++)
    {
        _system[p].print(file);
    }
    
    file << "===/ SOLAR SYSTEM === " << endl;
}

////////

vector<double> solver::mass_center(void) const
{
    
    return (_mass_center);
}

std::vector<planet> solver::system(void) const
{
    
    return (_system);
}






















