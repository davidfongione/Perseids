//
//  unit-tests.cpp
//  Program
//
//  Created by Antoine Hugounet on 24/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "classes/planet.hpp"
#include "classes/solver.hpp"
#include <cmath>

using namespace std;

int run_unittest(int argc, const char* argv[])
{
    
    return (Catch::Session().run(argc, argv));
}


TEST_CASE("several minor operations are tested", "[planet and solver]")
{
   
    planet _earth("earth", 6.E24, 8.30757514E-01, 5.54644964E-01, -9.79193739E-03, 1.42820162E-02);
    planet _jupiter("jupiter", 1.9E27, -4.54463137, -2.98088727, 4.05019642E-03, -5.95135698E-03);
    planet _mars("mars", 6.6E23, -1.60063680E+00, 4.51266379E-01, -3.22884752E-03, -1.22815747E-02);
    planet _sun("sun", 2.E30, 2.17112305E-03, 5.78452455E-03, -5.30635989E-06, 5.44444408E-06);
    planet _sun_masscenter("sun", 1.E23, 0., 0., 0., 0.);
    planet _test("test", 1.E20, 42., 0., 8827., 0.);
    
    solver system;

    SECTION("planet::distance()")
    {
        double x = 8.30757514E-01 - 2.17112305E-03;
        double y = 5.54644964E-01 - 5.78452455E-03;
        
        REQUIRE(_earth.distance(_sun) == sqrt(x*x + y*y));
        REQUIRE(_test.distance(_sun_masscenter) == 42.);
    }
    
    SECTION("planet::distance_center()")
    {
        double x = -1.60063680E+00;
        double y = 4.51266379E-01;
        
        REQUIRE(_mars.distance_center() == sqrt(x*x + y*y));
        REQUIRE(_test.distance_center() == 42.);
    }
    
    SECTION("planet : energies")
    {
        double kinetic = 0.5 * 1.E20 * 8827 * 8827;
        double potential = 4 * M_PI * M_PI * (1.E20 * 1.E23) / (42.*42.);
        double total = kinetic + potential;
        
        //REQUIRE(_test.kinetic_energy() == kinetic);
        //REQUIRE(_test.potential_energy(_sun_masscenter) == potential);
        //REQUIRE(_test.total_energy(_sun_masscenter) == total);
    }
    
    SECTION("solver::total_mass()")
    {
        double mass =  6.E24 + 1.9E27 + 6.6E23 + 2.E30;
        
        system.add(_earth);
        system.add(_jupiter);
        system.add(_mars);
        system.add(_sun);
        
        REQUIRE(system.total_mass() == mass);
    }
    
    SECTION("solver : mass center and energies")
    {
        
        vector<double> position = {0., 0.};
        double total_mass;
        
        system.add(_earth);
        
        /*
        system.add(_sun_masscenter);
                
        total_mass = system.total_mass();
        
        position[0] = (1 / total_mass) * _earth.mass() * _earth.position[0];
        position[1] = (1 / total_mass) * _earth.mass() * _earth.position[1];

        REQUIRE(system.mass_center() == position);*/
        REQUIRE(system.kinetic_energy() == _earth.kinetic_energy());
        

    }
}














