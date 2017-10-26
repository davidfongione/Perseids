//
//  models.hpp
//  Program
//
//  Created by Antoine Hugounet on 23/10/2017.
//  Copyright © 2017 Hugounet and Villeneuve. All rights reserved.
//

#pragma once

#include <string>

void es_euler(const double years, const std::string folder);
void ejs_verlet(const double years, const std::string folder);
void ejs_rmc_euler(const double years, const std::string folder);
void ejs_rmc_verlet(const double years, const std::string folder);
void fs_rmc_verlet(const double years, const std::string folder);
void free_model(const double years, const std::string folder);
void escape(const double years, std::string folder);
