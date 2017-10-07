//
//  planet.hpp
//  Program
//
//  Created by Antoine Hugounet on 06/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//


#pragma once


class planet
{
public:
    //  constructors
    planet(void);
    planet(double mass, double x, double y, double vx, double vy);
    //  methods
    double distance(const planet other);

private:
    double _position[2];
    double _velocity[2];
    double _mass;
};
