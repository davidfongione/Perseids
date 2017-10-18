//
//  planet.hpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//


#pragma once
#include <vector>
#include <string>


class planet
{
public:
    planet(void);
    planet(std::string name, double mass, double x, double y, double vx, double vy);
    planet(const planet& other);    //  probably useless but more secure to prevent C++'s bad behaviors
    
    //  data
    std::vector<double> position;
    std::vector<double> velocity;
    
    //  methods
    double distance(const planet& other) const;
    double distance_center(void) const;
    double grav_force(const planet& other) const;
    std::string name(void) const;

    double mass(void) const;

    double kinetic(void) const;
    double potential(const planet& other) const;
    double total(const planet& other) const;
    
private:
    double _mass;
    double _potential;
    double _kinetic;
    std::string _name;
};
