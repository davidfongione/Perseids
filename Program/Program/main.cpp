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
#include "initialisations.hpp"

using namespace std;

int main(int argc, const char * argv[])
{

    solver es_system;

    es_system.add(earth);
    es_system.add(sun);
    es_system.add(jupiter);
    es_system.add(mars);
    
    es_system.euler(20, 10000);
    
    cout << es_system.total_mass() << endl;
    cout << es_system.mass_center()[0] << endl;
    
    return 0;
}
