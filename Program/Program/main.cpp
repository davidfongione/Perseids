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


using namespace std;

int main(int argc, const char* argv[])
{

    if(run_unittest(0, nullptr) != 0)
    {
        cout << "Unittests failed." << endl;
        exit(1);
    }

    string main_folder = "/Users/antoinehugounet/Documents/Scolarité/UiO/FYS3150 - Computational physics/Project 3/Perseids/Program/Models/";
    
    escape(20., main_folder + "escape/");
    
    return 0;
}
