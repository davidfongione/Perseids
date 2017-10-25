//
//  main.cpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#include <iostream>
#include "models.hpp"
#include "unit-tests.hpp"
#include <cmath>


using namespace std;

int main(int argc, const char * argv[])
{
    
    if(run_unittest(0, nullptr) != 0)
    {
        cout << "Unittests failed." << endl;
        exit(1);
    }

    string main_folder = "/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/";
    
    /*
    es_euler(1, main_folder + "es_euler/");
    ejs_verlet(8., main_folder + "ejs_verlet/");
    ejs_rmc_euler(7., main_folder + "ejs_rmc_euler/");
    ejs_rmc_verlet(8., main_folder + "ejs_rmc_verlet/");
    fs_rmc_verlet(15., main_folder + "fs_rmc_verlet/");
    */
    
    return 0;
}
