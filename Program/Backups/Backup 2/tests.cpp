//
//  tests.cpp
//  Program
//
//  Created by Antoine Hugounet on 20/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#include "tests.hpp"
#include <iostream>
#include "planet.hpp"
#include "solver.hpp"
#include <string>

using namespace std;

void tests(void)
{
    
    cout << "=== TESTS ===" << endl;
    
    planet earth("earth", 6.E24, 8.30757514E-01, 5.54644964E-01, -9.79193739E-03, 1.42820162E-02);
    planet sun("sun", 2.E30, 2.17112305E-03, 5.78452455E-03, -5.30635989E-06, 5.44444408E-06);
    planet jupiter ("jupiter", 1.9E27, -4.54463137, -2.98088727, 4.05019642E-03, -5.95135698E-03);
    
    solver system;
    
    system.add(earth);
    system.add(sun);
    system.add(jupiter);
    
    cout << "Mass center /x: " << system.mass_center()[0] << endl;
    cout << "Mass center /y: " << system.mass_center()[1] << endl;
    cout << "Total mass: " << system.total_mass() << endl;
    cout << "Distance Earth-Sun: " << earth.distance_center() << endl;
    
    cout << "===/ TESTS ===" << endl;
}

