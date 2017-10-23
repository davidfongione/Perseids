//
//  models.hpp
//  Program
//
//  Created by Antoine Hugounet on 23/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#pragma once

#include <string>

void es_euler(const int years, std::string folder);
void ejs_verlet(const int years, std::string folder);
void ejs_rmc_euler(const int years, std::string folder);
void ejs_rmc_verlet(const int years, std::string folder);
void fs_rmc_verlet(const int years, std::string folder);
