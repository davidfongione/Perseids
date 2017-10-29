//
//  main.cpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "unit-tests.hpp"
#include "initialisations.hpp"
#include "classes/planet.hpp"
#include "classes/solver.hpp"
#include "time.h"
#include <cmath>

using namespace std;


int main(int argc, const char* argv[])
{
    
    if(run_unittest(0, nullptr) != 0)
    {
        cout << "Unittests failed." << endl;
        exit(1);
    }

    string folder = "/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Results/Peri/";
    
    solver system;
    system.add(sun_wmc);
    system.add(earth);
    
    system.verlet(200., folder);

    return 0;
}

