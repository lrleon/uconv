
/*
   _   _  ___ ___  _ ____   __
  | | | |/ __/ _ \| '_ \ \ / /  C++ Physical magnitudes and units conversion
  | |_| | (_| (_) | | | \ V /   Version 1.0
   \__,_|\___\___/|_| |_|\_/    https://github.com/lrleon/uconv

  This file is part of uconv library

  Copyright (c) 2018     Ixhel Mejias
                         Alberto Valderrama
                         Fernando Montilla
                         Eduardo Valderrama
                         Neylith Quintero
                         Felix Buccellato
                         Virginia Buccellato
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
*/
#ifndef DIAMETER_UNIT_H
#define DIAMETER_UNIT_H

# include "units.H"

Declare_Physical_Quantity(Diameter, "D", "D", R"DESC(The diameter is the measurement of a straight line passing from side to side through the center of a body or figure, especially a circle. It is used to designate the pipe size. The diameter is denoted as D.)DESC");


Declare_Unit(Foot_D, "ft_d", "ft", "The diameter measured in feet", Diameter, 8.3333333333333333e-2, 25);
Declare_Unit(Inch_D, "in", "in", "The diameter measured in inches", Diameter, 1, 300); 
Declare_Unit(Meter_D, "m", "m", "The diameter measured in meters", Diameter, 0.0254, 7.62); 
Declare_Unit(Centimeter_D, "cm", "cm", "The diameter measured in centimeters", Diameter, 2.54, 762); 
Declare_Unit(Millimeter_D, "mm", "mm", "The diameter measured in millimeters", Diameter, 25.4, 7620); 

// To Foot_D 
Declare_Conversion(Inch_D, Foot_D, V) { return 8.3333333333333333e-2 * V; }
Declare_Conversion(Meter_D, Foot_D, V) { return 3.28083989501 * V; }
Declare_Conversion(Centimeter_D, Foot_D, V) { return 3.28083989501e-2 * V; }
Declare_Conversion(Millimeter_D, Foot_D, V) { return 3.28083989501e-3 * V; }

// To Inch_D
Declare_Conversion(Foot_D, Inch_D, V) { return 12 * V; }
Declare_Conversion(Meter_D, Inch_D, V) { return 39.3700787402 * V; }
Declare_Conversion(Centimeter_D, Inch_D, V) { return 39.3700787402e-2 * V; }
Declare_Conversion(Millimeter_D, Inch_D, V) { return 39.3700787402e-3 * V; }

// To Meter_D
Declare_Conversion(Foot_D, Meter_D, V) { return 0.3048 * V; }
Declare_Conversion(Inch_D, Meter_D, V) { return 0.0254 * V; }
Declare_Conversion(Centimeter_D, Meter_D, V) { return 1e-2 * V; }
Declare_Conversion(Millimeter_D, Meter_D, V) { return 1e-3 * V; }

// To Centimeter_D
Declare_Conversion(Foot_D, Centimeter_D, V) { return 30.48 * V; }
Declare_Conversion(Inch_D, Centimeter_D, V) { return 2.54 * V; }
Declare_Conversion(Meter_D, Centimeter_D, V) { return 1e2 * V; }
Declare_Conversion(Millimeter_D, Centimeter_D, V) { return 0.1 * V; }

// To Millimeter_D
Declare_Conversion(Foot_D, Millimeter_D, V) { return 304.8 * V; }
Declare_Conversion(Inch_D, Millimeter_D, V) { return 25.4 * V; }
Declare_Conversion(Meter_D, Millimeter_D, V) { return 1e3 * V; }
Declare_Conversion(Centimeter_D, Millimeter_D, V) { return 10 * V; }


// References:
// http://petrowiki.org/Recommended_SI_units_and_conversion_factors#Additional_Conversion_Factors
// http://petrowiki.org/Basic_symbols_in_alphabetical_order
// Brown, K. (1977). The Technology of Artificial Lift Methods. ISBN: 0-87814-031-X.

#endif // DIAMETER_UNIT_H
