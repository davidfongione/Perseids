//
//  solver-private.cpp
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
#include <iomanip>

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
    _next_acc = other._prev_acc;
}


//  main algorithms


void solver::euler(const double years, const std::string folder)
{
    //  equations in 1D :
    //  x(t+dt) = dt*v(t) + x(t)
    //  v(t+dt) = dt*a(t) + v(t) = dt*Fx/m + v(t), with Newton's law
    
    int timesteps;
    double h;
    string path;
    ofstream output;
    
    timesteps = (int) (years * 250);
    h = ((double) years) / ((double) timesteps);
    
    for(int i = 0; i <= timesteps; i++)
    {
        for(int k = 0; k < _card; k++)
        {
            path = folder + _system[k].name();
            
            if(i == 0)
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
        
        _print_kinetic_energy(i, folder);
        _print_potential_energy(i, folder);
        _print_total_energy(i, folder);
        _update_quantities(i, h);
    }
    
    _gnuplot(folder, years);
    _gnuplot_png(folder, years);
    _gnuplot_energies(folder, years);
    _gnuplot_energies_png(folder, years);
    
    _time += years;
}

////////

void solver::verlet(const double years, const std::string folder, const bool relativity, const bool high_res)
{
    //  equations in 1D :
    //  x(t+dt) = x(t) + dt*v(t) + (1/2)(dt^2)*a(t)
    //  v(t+dt) = v(t) + (1/2)*dt*[a(t) + a(t+dt)]
    
    int timesteps;
    double h;
    double h_squared;
    double radical;
    bool can_write;
    string path;
    ofstream output;
    vector<vector<double>> next_acc;   //  vector for a(t+dt)
    
    //  360*3600*7 precision iff asked by the user or for a relativistic simulation
    //  else a 1 day time step is sufficient enough
    timesteps = (high_res || relativity) ? ((int) years * 9072000) : ((int) years * 365);
    
    h = ((double) years) / ((double) timesteps);
    h_squared = h * h;
    
    for(int i = 0; i <= timesteps; i++)
    {
        //  can_write = !relativity || (i % (3600 * 7) == 0);
        // can_write = (i % (3600 * 7) == 0);

        //  with a high res or the relativity, the program takes a too
        //  long time to write in documents (about 60mn)
        //  as a consequence, it outputs only the last values and
        //  outputs all the value only in the standard mode
        can_write = (high_res || relativity) ? (i == timesteps) : true;
        
        for(int k = 0; k < _card; k++)
        {
            
            if(i == 0)
            {
                path = folder + _system[k].name();
                output.open(path);  //  erase the previous file
                output << "Velocity-Verlet algorithm (2D)" << endl;
                output << _system[k].name() << " (x, y, vx, vy)" << endl;
                output << "Timestep: " << years << " years" << endl ;
                output << "Relativistic correction: " << boolalpha << relativity << endl;
                output << "High resolution: " << high_res << relativity << endl << endl;
                output.close();
            }
            
            if(can_write)
            {
                path = folder + _system[k].name();
                output.open(path, ios::app);   //  write after the existing content
                _system[k].print_pos(output);
                output.close();
            }
            
            radical = 0.5 * h_squared;
            
            _system[k].position[0] = _prev_pos[k][0] + h * _prev_vel[k][0] + radical * _prev_acc[k][0];
            _system[k].position[1] = _prev_pos[k][1] + h * _prev_vel[k][1] + radical * _prev_acc[k][1];
        }
        
        _next_acc = _next_acceleration(relativity);
        
        for(int k = 0; k < _card; k++)
        {
            if(can_write)
            {
                path = folder + _system[k].name();
                output.open(path, ios::app);
                _system[k].print_vel(output);
                _print_kinetic_energy(i, folder);
                _print_potential_energy(i, folder);
                _print_total_energy(i, folder);
                output << endl;
                output.close();
            }
            
            radical = 0.5 * h;
            
            _system[k].velocity[0] = _prev_vel[k][0] + radical * (_prev_acc[k][0] + _next_acc[k][0]);
            _system[k].velocity[1] = _prev_vel[k][1] + radical * (_prev_acc[k][1] + _next_acc[k][1]);
        }
        
        _update_quantities(i, h, _next_acc);
    }
    
    _gnuplot(folder, years);
    _gnuplot_png(folder, years);
    _gnuplot_energies(folder, years);
    _gnuplot_energies_png(folder, years);
    
    _time += years;
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
    
    for(auto& body : _system)
    {
        energy += body.kinetic_energy();
    }
    
    return (energy);
}

////////

double solver::potential_energy(void) const
{
    double energy = 0.;
    
    for(auto& body : _system)
    {
        energy += body.potential_energy(_system);
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
    //  only normalizes the mass and the velocity
    _system.push_back(body);
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


///////


void solver::_gnuplot(const std::string folder, const double years) const
{
    ofstream outplot;
    string output_path;
    string style;
    string title;
    vector<string> path(_card);    //  path to each data file
    
    output_path = folder + "Gnuplot/plot.gnu";
    outplot.open(output_path);
    
    style = " using 1:2 w l lt rgb ";
    
    outplot << "reset" << endl;
    outplot << "set size ratio -1" << endl;
    outplot << "set title 'Time-step: " << to_string(years) << " years'" << endl;
    outplot << "set xlabel 'distance (AU)'" << endl;
    outplot << "set ylabel 'distance (AU)'" << endl << endl;
    
    for(int k = 0; k < _card; k++)
    {
        path[k] = "'" + folder + _system[k].name() + "'";
        title = " title '" + _system[k].name() + "'";
        
        if(k == 0)
        {
            outplot << "plot " + path[k] + style + _gnuplot_colors(k) + title << endl << endl;
        }
        else
        {
            outplot << "replot " + path[k] + style + _gnuplot_colors(k) + title << endl << endl;
        }
    }
    
    outplot.close();
}

////////

void solver::_gnuplot_png(const std::string folder, const double years) const
{
    ofstream outplot;
    string output_path;
    string style;
    string title;
    vector<string> path(_card);    //  path to each data file
    
    output_path = folder + "Gnuplot/plot-png.gnu";
    outplot.open(output_path);
    
    style = " using 1:2 w l lt rgb ";
    
    outplot << "reset" << endl;
    outplot << "set terminal png enhanced size 1000, 1000" << endl;
    outplot << "set output " << "'" << folder << "Gnuplot/plot.png'" << endl;
    outplot << "set size ratio -1" << endl;
    outplot << "set title 'Time-step: " << to_string(years) << " years'" << endl;
    outplot << "set xlabel 'distance (AU)'" << endl;
    outplot << "set ylabel 'distance (AU)'" << endl << endl;
    
    for(int k = 0; k < _card; k++)
    {
        path[k] = "'" + folder + _system[k].name() + "'";
        title = " title '" + _system[k].name() + "'";
        
        if(k == 0)
        {
            // plot earth using 1:2 w l lt rgb "blue" title 'Earth'
            outplot << "plot " + path[k] + style + _gnuplot_colors(k) + title;
        }
        else
        {
            outplot << ", " + path[k] + style + _gnuplot_colors(k) + title;
        }
    }
    
    outplot.close();
}

////////

void solver::_gnuplot_energies(const std::string folder, const double years) const
{
    ofstream outplot;
    string output_path;
    string style;
    string title;
    vector<string> path(_card);    //  path to each data file
    
    output_path = folder + "Gnuplot/plot-energies.gnu";
    outplot.open(output_path);
    
    outplot << "reset" << endl;
    outplot << "set size ratio -1" << endl;
    outplot << "set title 'Time-step: " << to_string(years) << " years'" << endl;
    outplot << "set xlabel 'Time (year)'" << endl;
    outplot << "set ylabel 'Energie (kg*AU^2 / year^2)'" << endl << endl;
    outplot << "kinetic = '" << folder << "/system-kinetic-energy" << endl;
    outplot << "potential = '" << folder << "/system-potential-energy" << endl << endl;
    outplot << "total = '" << folder << "/system-total-energy" << endl;
    outplot << "plot kinetic using 1:2 w l title 'Kinetic energy'" << endl;
    outplot << "replot potential using 1:2 w l title 'Potential energy'" << endl;
    outplot << "replot total using 1:2 w l title 'Total'" << endl;
    
    outplot.close();
}

////////

void solver::_gnuplot_energies_png(const std::string folder, const double years) const
{
    ofstream outplot;
    string output_path;
    string style;
    string title;
    vector<string> path(_card);    //  path to each data file
    
    output_path = folder + "Gnuplot/plot-energies-png.gnu";
    outplot.open(output_path);
    
    outplot << "reset" << endl;
    outplot << "set terminal png enhanced size 1000, 1000" << endl;
    outplot << "set output " << "'" << folder << "Gnuplot/plot-energies.png'" << endl;
    outplot << "set size ratio -1" << endl;
    outplot << "set title 'Time-step: " << to_string(years) << " years'" << endl;
    outplot << "set xlabel 'Time (year)'" << endl;
    outplot << "set ylabel 'Energie (kg*AU^2 / year^2)'" << endl << endl;
    outplot << "kinetic = '" << folder << "/system-kinetic-energy" << endl;
    outplot << "potential = '" << folder << "/system-potential-energy" << endl << endl;
    outplot << "total = '" << folder << "/system-total-energy" << endl;
    outplot << "plot kinetic using 1:2 w l title 'Kinetic energy', potential using 1:2 w l title 'Potential energy', total using 1:2 w l title 'Total'" << endl;
    
    outplot.close();
}


////////

void solver::_print_kinetic_energy(const int i, const std::string folder) const
{
    ofstream output;
    string space = "        ";
    
    if(i == 0)
    {
        output.open(folder + "system-kinetic-energy");
    }
    else
    {
        output.open(folder + "system-kinetic-energy", ios::app);
    }
    output << _time << setprecision(8) << space << kinetic_energy() << endl;
    
    output.close();
}

////////

void solver::_print_potential_energy(const int i, const std::string folder) const
{
    ofstream output;
    string space = "        ";
    
    if(i == 0)
    {
        output.open(folder + "system-potential-energy");
    }
    else
    {
        output.open(folder + "system-potential-energy", ios::app);
    }
    output << _time << setprecision(8) << space << potential_energy() << endl;
    
    output.close();
}


////////

void solver::_print_total_energy(const int i, const std::string folder) const
{
    ofstream output;
    string space = "        ";
    
    if(i == 0)
    {
        output.open(folder + "system-total-energy");
    }
    else
    {
        output.open(folder + "system-total-energy", ios::app);
    }
    output << _time << setprecision(8) << space << total_energy() << endl;
    
    output.close();
}

////////

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

////////

void solver::_update_quantities(const int i, const double h)
{
    for(int k = 0; k < _card; k++)
    {
        _prev_pos[k] = _system[k].position;
        _prev_vel[k] = _system[k].velocity;
        _prev_acc[k] = _acceleration(k, false);
        _system[k].time = i * h;
    }
    _time = i * h;
}

////////

void solver::_update_quantities(const int i, const double h, std::vector<std::vector<double>> acc)
{
    for(int k = 0; k < _card; k++)
    {
        _prev_pos[k] = _system[k].position;
        _prev_vel[k] = _system[k].velocity;
        _system[k].time = i * h;
    }
    
    _prev_acc = acc;
    _time = i * h;
}


////////

vector<double> solver::_acceleration(const int p, const bool relativity) const
{
    //  p is the index of the planet for which we calculate eta
    
    double const g_const = 4 * M_PI * M_PI;
    double radical;
    double r;
    vector<double> relative_pos = {0., 0.};
    vector<double> acceleration = {0., 0.};
    
    if(_system[p].distance_center() != 0.)  //  avoid calculating a planet's acceleration with respect to itself
    {
        for(int k = 0; k < _card; k++)
        {
            if(k != p)
            {
                //  time/distance units are normalized with the constant 4*pi*pi
                r = _system[p].distance(_system[k]);
                double r_squared = r * r;
                radical = (_system[k].mass()) / (r_squared * r);
                
                relative_pos[0] = _system[p].position[0] - _system[k].position[0];
                relative_pos[1] = _system[p].position[1] - _system[k].position[1];
                
                acceleration[0] -= radical * relative_pos[0];
                acceleration[1] -= radical * relative_pos[1];
                if(relativity)
                {
                    double correction;
                    double cross;
                    double const c = 63241.0770;
                    cross = _system[k].position[0] * _system[k].velocity[1] + _system[k].position[1] * _system[k].velocity[0];
                    correction = (1. + (3. * cross) / (r_squared * c * c));
                    acceleration[0] *= correction;
                    acceleration[1] *= correction;
                }
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

////////

std::vector<std::vector<double>> solver::_next_acceleration(const bool relativity) const
{
    vector<vector<double>> acceleration;
    
    for(int k = 0; k < _card; k++)
    {
        acceleration.push_back(_acceleration(k, relativity));
    }
    
    return (acceleration);
}

////////

std::string solver::_gnuplot_colors(const int k) const
{
    string color;
    
    if(_system[k].name() == "earth") color = "\"blue\"";
    else if(_system[k].name() == "jupiter") color = "\"light-goldenrod\"";
    else if(_system[k].name() == "mercury") color = "\"orange-red\"";
    else if(_system[k].name() == "mars") color = "\"brown\"";
    else if(_system[k].name() == "neptune") color = "\"royalblue\"";
    else if(_system[k].name() == "saturn") color = "\"goldenrod\"";
    else if(_system[k].name() == "sun") color = "\"black\"";
    else if(_system[k].name() == "uranus") color = "\"light-blue\"";
    else if(_system[k].name() == "venus") color = "\"dark-goldenrod\"";
    else color = "dark-violet";
    
    return (color);
}
