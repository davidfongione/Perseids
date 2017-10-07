//
//  solver.hpp
//  Program
//
//  Created by Antoine Hugounet on 06/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//


#pragma once
#include <vector>
#include "planet.hpp"



class solver
{
public:
    
    friend class planet;
    
    //  constructor
    solver(void);
    
    //  methods
    void add_planet(const planet new_planet);
    
private:
    
    int _n_planets;
    double _G;
    std::vector<planet> _planets;
};
