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

using namespace std;



void solver::_gnuplot(const std::string folder, const double years) const
{
    
    ofstream outplot;
    string output_path;
    string style;
    string title;
    vector<string> path(_card);    //  path to each data file
    
    output_path = folder + "plot.gnu";
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
    
    output_path = folder + "plot-png.gnu";
    outplot.open(output_path);
    
    style = " using 1:2 w l lt rgb ";
    
    outplot << "reset" << endl;
    outplot << "set terminal png enhanced size 1000, 1000" << endl;
    outplot << "set output " << "'" << folder << "plot.png'" << endl;
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

void solver::_print_total_energy(const std::string folder, const int i) const
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
    output << _time << space << total_energy() << endl;
    
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
        _prev_acc[k] = _acceleration(k);
        _system[k].time = i * h;
    }
    _time = i * h;
}

////////

vector<double> solver::_acceleration(const int p) const
{
    
    //  p is the index of the planet for which we calculate eta
    
    double const g_const = 4 * M_PI * M_PI;
    double radical;
    double r;
    vector<double> relative_pos = {0., 0.};
    vector<double> acceleration = {0., 0.};
    
    if(_system[p].distance_center() != 0.)
    {
        for(int k = 0; k < _card; k++)
        {
            if(k != p)
            {
                //  time/distance units are normalized with the constant 4*pi*pi
                r = _system[p].distance(_system[k]);
                radical = (_system[k].mass()) / (r*r*r);
                
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

////////

std::vector<std::vector<double>> solver::_next_acc(void) const
{
    
    vector<vector<double>> acceleration;
    
    for(int k = 0; k < _card; k++)
    {
        acceleration.push_back(_acceleration(k));
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
