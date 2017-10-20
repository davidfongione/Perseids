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
#include <fstream>


class planet
{
public:
    
    planet(void);
    planet(std::string name, double mass, double x, double y, double vx, double vy);
    planet(const planet& other);
    
    //  data members
    int time;   //  in years
    std::vector<double> position;
    std::vector<double> velocity;
    
    //  methods
    int dim(void) const;
    double distance(const planet& other) const;
    double distance_center(void) const;
    double kinetic_energy(void) const;
    double mass(void) const;
    double potential_energy(const std::vector<planet>& system) const;
    double total_energy(const std::vector<planet>& system) const;
    void print(std::ofstream& file) const;
    void print_brut(std::ofstream& file) const;
    void normalize(void);   //  normalize with the good time & distance units
    std::string name(void) const;

    

    
private:
    
    int _dim;
    double _mass;
    std::string _name;
};
