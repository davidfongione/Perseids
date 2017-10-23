//
//  main.cpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#include <iostream>
#include "classes/planet.hpp"
#include "classes/solver.hpp"
#include <cmath>
#include "initialisations_nasa.hpp"

using namespace std;

int main(int argc, const char * argv[])
{

    int time_step;
    solver system;

    system.add(earth);
    system.add(jupiter);
    system.add(mars);
    system.add(mercury);
    system.add(neptune);
    system.add(saturn);
    system.add(sun_calculated);
    system.add(venus);
    system.add(uranus);
    
    // cout << "Enter a time-step (years): ";
    // cin >> time_step;
    // cout << "processing..." << endl;
    // system.verlet(time_step);
    
    return 0;
}
