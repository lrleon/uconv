/*
   _   _  ___ ___  _ ____   __
  | | | |/ __/ _ \| '_ \ \ / /  C++ Physical magnitudes and units conversion
  | |_| | (_| (_) | | | \ V /   Version 1.0
   \__,_|\___\___/|_| |_|\_/    https://github.com/lrleon/uconv

  This file is part of uconv library

  Copyright (c) 2018     Ixhel Mejias
                         Alberto Valderrama
                         Leandro Rabindranath Leon

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <https://www.gnu.org/licenses/>.
*/#ifndef LENGTH_UNIT_H
#define LENGTH_UNIT_H

# include "uconv.H"

Declare_Physical_Quantity(Length, "L", "L", R"DESC(The length is the measurement or extent of something. It may represent reservoir thickness, 				  drainage radius, well radius, etc.)DESC");


Declare_Unit(foot, "ft", "ft", "The length measured in feet", Length, 0, 98425.1968503937);
Declare_Unit(inch, "in", "in", "The length measured in inches", Length, 0, 1181102.36220472); 
Declare_Unit(meter, "m", "m", "The length measured in meters", Length, 0, 30000); 
Declare_Unit(yard, "yd", "yd", "The length measured in yards", Length, 0, 32808.3989501312); 

// To foot 
Declare_Conversion(inch, foot, V) { return 8.3333333333333333e-2 * V; }
Declare_Conversion(meter, foot, V) { return 3.28083989501 * V; }
Declare_Conversion(yard, foot, V) { return  3 * V; }

// To inch
Declare_Conversion(foot, inch, V) { return 12 * V; }
Declare_Conversion(meter, inch, V) { return 39.3700787402 * V; }
Declare_Conversion(yard, inch, V) { return  36 * V; }

// To meter
Declare_Conversion(foot, meter, V) { return 0.3048 * V; }
Declare_Conversion(inch, meter, V) { return 0.0254 * V; }
Declare_Conversion(yard, meter, V) { return 0.9144 * V; }

// To yard
Declare_Conversion(foot, yard, V) { return 0.33333333333333337 * V; }
Declare_Conversion(inch, yard, V) { return 0.027777777777777776 * V; }
Declare_Conversion(meter, yard, V) { return 1.0936132983377078 * V; }

#endif // LENGTH_UNIT_H
