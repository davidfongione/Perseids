//
//  main.cpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#include <iostream>
#include "planet.hpp"
#include "solver.hpp"
#include "tests.hpp"
#include <cmath>

using namespace std;

int main(int argc, const char * argv[])
{

    planet test("earth", 6.E24, 1., 0., 0., 2*M_PI);
    planet sun("sun", 1., 0., 0., 0., 0.);
    planet earth("earth", 6.E24, 8.30757514E-01, 5.54644964E-01, -9.79193739E-03, 1.42820162E-02);
    solver es_system;

    earth.normalize();
    sun.normalize();
    es_system.add(earth);
    es_system.add(sun);

    
    es_system.euler(5., 10000); //  instable par rapport aux meshpoints

    
    return 0;
}
