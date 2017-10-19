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
    
    //  methods
    int size(void) const;
    double kinetic_energy(void) const;
    double potential_energy(void) const;
    double total_energy(void) const;
    double total_mass(void) const;
    void add(const planet& other);
    void euler(const int time, const int meshpoints);
    void print(std::ofstream& file) const;  //  prints the system's last position and velocity
    std::vector<double> mass_center(void) const;
    std::vector<planet> object(void) const;
    
private:

    int _card;          //  number of planets in the system
    int _time;          //  t_final of the system, in years
    double _total_mass;
    std::vector<planet> _system;
    std::vector<double> _mass_center;
    std::vector<double> _eta(const int p) const;
};
