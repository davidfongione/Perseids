//
//  main.cpp
//  Program
//
//  Created by Antoine Hugounet on 08/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#include "models.hpp"


using namespace std;

int main(int argc, const char * argv[])
{

    string main_folder = "/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/";
    
    es_euler(1, main_folder + "es_euler/");
    ejs_verlet(7., main_folder + "ejs_verlet/");
    ejs_rmc_euler(7., main_folder + "ejs_rmc_euler/");
    ejs_rmc_verlet(7., main_folder + "ejs_rmc_verlet/");
    fs_rmc_verlet(15., main_folder + "fs_rmc_verlet/");
    
    
    return 0;
}
