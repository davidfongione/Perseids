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
    
    //  constructors
    
    planet(void);
    planet(std::string name, double mass, double x, double y, double vx, double vy);
    planet(const planet& body);
    
    //  data
    
    int time;   //  in years
    std::vector<double> position;
    std::vector<double> velocity;
    
    //  getters
    
    int dim(void) const;
    double mass(void) const;
    std::string name(void) const;
    
    //  methods
    
    double distance(const planet& body) const;
    double distance_center(void) const;
    double kinetic_energy(void) const;
    double potential_energy(const std::vector<planet>& system) const;
    double total_energy(const std::vector<planet>& system) const;
    void normalize(void);   //  normalize with the good time & distance units
    void print(std::ofstream& output) const;
    void print_pos(std::ofstream& output) const;
    void print_vel(std::ofstream& output) const;
    
    
private:
    
    //  data
    
    int _dim;
    double _mass;
    std::string _name;
};
