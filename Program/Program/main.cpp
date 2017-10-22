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
#include <cmath>
#include "initialisations.hpp"

using namespace std;

int main(int argc, const char * argv[])
{

    solver es_system;

    es_system.add(earth);
    es_system.add(jupiter);
    es_system.add(mars);
    es_system.add(mercury);
    es_system.add(neptune);
    es_system.add(saturn);
    es_system.add(sun);
    es_system.add(venus);
    es_system.add(uranus);
    es_system.add(moon);
    
    es_system.verlet(6);
    
    return 0;
}
