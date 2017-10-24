//
//  solver.hpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//


#pragma once
#include <array>
#include <vector>
#include "planet.hpp"
#include <fstream>



class solver
{
    friend class planet;
    
public:
    
    //  constructors
    
    solver(void);
    solver(const solver& other);
    
    //  main algorithms
    
    void euler(const double years, const std::string folder);
    void verlet(const double years, const std::string folder);
    
    //  getters
    
    int size(void) const;
    double time(void) const;
    double total_mass(void) const;
    
    //  methods

    double kinetic_energy(void) const;
    double potential_energy(void) const;
    double total_energy(void) const;
    void add(planet body);
    void print(std::ofstream& file) const;  //  prints the system's last position and velocity
    std::vector<double> mass_center(void) const;
    std::vector<planet> system(void) const;

    
private:

    //  data
    
    int _card;  //  number of planets in the system
    double _time;  //  t_0 of the system, in years
    double _total_mass;
    std::vector<double> _mass_center;
    std::vector<std::vector<double>> _prev_pos;
    std::vector<std::vector<double>> _prev_vel;
    std::vector<std::vector<double>> _prev_acc;
    std::vector<planet> _system;
    
    //  methods
    
    void _gnuplot(const std::string folder, const double years) const;
    void _gnuplot_png(const std::string folder, const double years) const;
    void _print_energy(std::ofstream& file) const;
    void _update_mass_center(const planet& body);
    void _update_quantities(const int i, const double h);
    std::vector<double> _acceleration(const int p) const;
    std::vector<std::vector<double>> _next_acc(void) const;
    std::string _gnuplot_colors(const int k) const;
};
