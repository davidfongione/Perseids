//
//  main.cpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#include <iostream>
#include "unit-tests.hpp"
#include "initialisations.hpp"
#include "classes/planet.hpp"
#include "classes/solver.hpp"
#include "time.h"


using namespace std;

int main(int argc, const char* argv[])
{

    if(run_unittest(0, nullptr) != 0)
    {
        cout << "Unittests failed." << endl;
        exit(1);
    }

    string main_folder = "/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Test/";
    
    solver system;
    system.add(sun_wmc);
    system.add(mercury_peri);
    
    clock_t start;
    clock_t finish;
    double time;
    
    start = clock();
    system.verlet(100., main_folder + "Peri/", true);
    finish = clock();
    
    time = ((double) finish - start) / ((double) CLOCKS_PER_SEC);
    cout << time << endl;
    
    return 0;
}
