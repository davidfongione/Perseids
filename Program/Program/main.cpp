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

double mercury_precession(const double years, const std::string folder);


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
    system.add(mercury_peri);
    
    system.verlet(100., folder, false, true);
    

    return 0;
}


double mercury_precession(const double years, const std::string folder)
{
    double x;
    double y;
    double theta;
    
    solver system;
    system.add(sun_wmc);
    system.add(mercury_peri);
    
    system.verlet(years, folder, true, true);
    
    x = system.system()[1].position[0];
    y = system.system()[1].position[1];
    theta = atan(y / x);
    
    cout << "xp=" << setprecision(12) << x << endl;
    cout << "yp=" << setprecision(12) << y << endl;
    cout << "Thetap: " << setprecision(12) << theta << endl;
    
    return (theta);
}
