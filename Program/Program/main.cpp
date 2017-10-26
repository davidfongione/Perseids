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


using namespace std;

int main(int argc, const char* argv[])
{

    if(run_unittest(0, nullptr) != 0)
    {
        cout << "Unittests failed." << endl;
        exit(1);
    }

    string main_folder = "/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Résultats/Modèle à trois planètes/Faux centre de masse/";
    
    solver system;
    system.add(earth_ejs_wmc);
    system.add(jupiter_ejs_wmc);
    system.add(sun_ejs_wmc);
    
    system.verlet(100., main_folder);
    
    
    return 0;
}
