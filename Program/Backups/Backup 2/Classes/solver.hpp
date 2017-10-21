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
    
    solver(void);
    solver(const solver& other);
    
    //  methods
    int size(void) const;
    double kinetic_energy(void) const;
    double potential_energy(void) const;
    double total_energy(void) const;
    double total_mass(void) const;
    void add(planet other);
    void euler(const double years, const int meshpoints);
    void print(std::ofstream& file) const;  //  prints the system's last position and velocity
    std::vector<double> mass_center(void) const;
    std::vector<planet> system(void) const;
    
private:

    int _card;  //  number of planets in the system
    double _time;  //  t_0 of the system, in years
    double _total_mass;
    std::vector<planet> _system;
    std::vector<double> _mass_center;
    std::vector<double> _acceleration(const int p) const;
};