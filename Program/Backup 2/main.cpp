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

using namespace std;

int main(int argc, const char * argv[])
{

    planet sun("sun", 2.E30, 0., 0., 0., 0.);
    planet earth("earth", 6.E24, 9.851577702404218E-01, 1.917376133839731E-01, -3.486360100992620E-03, 1.683858057526111E-02);
    solver es_system;

    //es_system.add(sun);
    es_system.add(earth);

    es_system.euler(1., 100);

    return 0;
}
