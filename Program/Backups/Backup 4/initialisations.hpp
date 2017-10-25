//
//  initialisations.hpp
//  Program
//
//  Created by Antoine Hugounet on 21/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#pragma once
#include <cmath>
#include "classes/planet.hpp"

//  planets initialisations

//  data from the NASA, to be obtained at https://ssd.jpl.nasa.gov/horizons.cgi#top
//  27.10.2017, 00:00:00

planet earth("earth", 6.E24, 8.30757514E-01, 5.54644964E-01, -9.79193739E-03, 1.42820162E-02);
planet jupiter ("jupiter", 1.9E27, -4.54463137, -2.98088727, 4.05019642E-03, -5.95135698E-03);
planet mars("mars", 6.6E23, -1.60063680E+00, 4.51266379E-01, -3.22884752E-03, -1.22815747E-02);
planet mercury("mercury", 3.3E23, -1.537256803720000E-01, -4.326509049973161E-01, 2.084982792680136E-02, -8.026395475494962E-03);
planet neptune("neptune", 1.03E26, 2.862286355822386E+01, -8.791151564880529E+00, 9.010839253968958E-04, 3.019851091079401E-03);
planet saturn("saturn", 5.5E26, -3.000365464147523E-01, -1.005121487413227E+01, 5.269787506575000E-03, -1.837774500581324E-04);
planet sun("sun", 2.E30, 2.17112305E-03, 5.78452455E-03, -5.30635989E-06, 5.44444408E-06);
planet uranus("uranus", 8.8E25, 1.784192250600989E+01, 8.843248837812927E+00, -1.775564692276439E-03, 3.340680253439256E-03);
planet venus("venus", 4.9E24, -7.049960476048377E-01, 1.312910376443176E-01, -3.646727612165235E-03, -1.999997620788355E-02);


//  data calculated manually

planet earth_calculated("earth", 6.E24, 1., 0., 2*M_PI, 0.);
planet sun_mass_center("sun", 2.E30, 0, 0, 0, 0);
planet sun_calculated("sun", 2.E30,  2.17112305E-03, 5.78452455E-03, -3.818310791E-6, 5.61094309E-6);
planet jupiter_calculated("jupiter", 1.9E27, 1.5237, 0., 2.*M_PI / sqrt(1.5237), 0.);
planet sun_nomass("sun", 0, 2.17112305E-03, 5.78452455E-03, -5.30635989E-06, 5.44444408E-06);

