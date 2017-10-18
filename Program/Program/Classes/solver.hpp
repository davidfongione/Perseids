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
    ~solver();
    
    //  methods
    void add(const planet& other);
    void print(std::ofstream& file, const int dim) const;
    void euler(const int h);
    std::vector<double> mass_center(void) const;
    
private:
    //  utility data
    int _card;          //  number of planets in the system
    int _meshpoints;    //  number of meshpoints
    
    //  physical data, multi array with the positions/velocity of the planets
    double*** _sys_pos; //  sys_position[planet number][meshpoint index][0 for x or 1 for y]
    double*** _sys_vel; //  idem for the velocity
    std::vector<planet> _system;
    
    //  utilities methods
    std::vector<double> _eta(const std::vector<planet>& system, const double*** sys_pos, const int p, const int i) const;
    double _total_mass(void) const;
};
