
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
#ifndef POWER_UNIT_H
#define POWER_UNIT_H

# include "uconv.H"

Declare_Physical_Quantity(Power, "P", "P",
			  "power is the rate of doing work. It is the amount of "
			  "energy consumed per unit time");

Declare_Unit(HorsePower, "hp", "hp",
	     "Unit of measurement of power hp", Power, 0, 2000);

Declare_Unit(Watt, "W", "W", "Unit of measurement of power watt", Power, 0,
	     1491399.74316);

// To HorsePower
Declare_Conversion(Watt, HorsePower, V) { return 1.3410220896e-3 * V; }

// To watt
Declare_Conversion(HorsePower, Watt, V) { return 745.699871582 * V; }

#endif
