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
*/
# ifndef TEMPERATURE_UNIT_H
# define TEMPERATURE_UNIT_H

# include "uconv.H"

Declare_Physical_Quantity(Temperature, "T", "T",
			  "Average thermal energy of the particles in a substance");

Declare_Unit(Kelvin, "degK","K",
	     "Absolute scale where the zero is the lowest temperature",
	     Temperature, 0, 672.03886667);
Declare_Unit(Celsius, "degC","\\degree{C}",
	     "Scale based on water freezing (0) and boiling point (100)",
	     Temperature, -273.15, 398.88888889);
Declare_Unit(Fahrenheit, "degF","\\degree{F}", 
	     "Scale based on brine freezing (0) and boiling point (100)",
	     Temperature, -459.67, 750);
Declare_Unit(Rankine, "degR","\\degree{R}", "Absolute scale of temperature",
	     Temperature, 0, 1209.67);

// To Fahrenheit 
Declare_Conversion(Kelvin, Fahrenheit, t) { return 1.8 * t - 459.67; }
Declare_Conversion(Celsius, Fahrenheit, t) { return 1.8 * t + 32; }
Declare_Conversion(Rankine, Fahrenheit, t) { return t - 459.67; }


// To Celsius
Declare_Conversion(Rankine, Celsius, t) { return (t - 491.67) / 1.8; }
Declare_Conversion(Kelvin, Celsius, t) { return t - 273.15; }
Declare_Conversion(Fahrenheit, Celsius, t) { return (t - 32) / 1.8; }


// To Rankine
Declare_Conversion(Fahrenheit, Rankine, t) { return t + 459.67; }
Declare_Conversion(Celsius, Rankine, t) { return (t + 273.15) * 1.8; }
Declare_Conversion(Kelvin, Rankine, t) { return 1.8 * t; }


// To Kelvin
Declare_Conversion(Fahrenheit, Kelvin, t) { return (t + 459.67) / 1.8; }
Declare_Conversion(Rankine, Kelvin, t) { return t / 1.8; }
Declare_Conversion(Celsius, Kelvin, t) { return t + 273.15; }


# endif // TEMPERATURE_UNIT_H
