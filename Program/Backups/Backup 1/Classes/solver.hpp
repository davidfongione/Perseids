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
    solver(const int meshpoints);
    ~solver();
    
    //  methods
    double kinetic_energy(void) const;
    double potential_energy(void) const;
    double total_energy(void) const;
    void add(const planet& other);
    void euler(const int h);
    void plot(void) const;
    void print(std::ofstream& file) const;
    std::vector<double> mass_center(void) const;
    
private:

    int _card;          //  number of planets in the system
    int _meshpoints;    //  number of meshpoints
    double _total_mass(void) const;
    double*** _sys_pos; //  [planet index][meshpt index][0 for x, 1 for y]
    double*** _sys_vel; //  idem
    std::vector<planet> _system;
    std::vector<double> _eta(const int p, const int i) const;
};
