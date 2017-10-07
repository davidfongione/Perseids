//
//  solver.cpp
//  Program
//
//  Created by Antoine Hugounet on 06/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//


#include "solver.hpp"



//  constructor

solver::solver(void)
{
    
    _G = 6.67408e-11;
}


//  methods

void solver::add_planet(const planet new_planet)
{
    _n_planets++;
    _planets.push_back(new_planet);
}

