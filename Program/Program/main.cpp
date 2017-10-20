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

    planet sun("sun", 2.E30, 0., 0., 0., 0.);
    planet earth("earth", 6.E24, 8.30757514E-01, 5.54644964E-01, -9.79193739E-03, 1.42820162E-02);
    planet jupiter ("jupiter", 1.9E27, -4.54463137, -2.98088727, 4.05019642E-03, -5.95135698E-03);
    solver es_system;

    es_system.add(earth);
    es_system.add(sun);
    es_system.add(jupiter);

    es_system.euler(5, 10000);
    
    cout << es_system.time() << endl;
    cout << es_system.total_mass() << endl;
    cout << es_system.mass_center()[0] << endl;

    return 0;
}
