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
*/# ifndef VELOCITY_UNIT_H
# define VELOCITY_UNIT_H

# include "uconv.H"

Declare_Physical_Quantity(Velocity, "V", "V", "Rate of change of position");

Declare_Unit(Ft_S, "ft/s", "ft/s", "feet for second", Velocity, 0, 1e6);

Declare_Unit(Meter_S, "m/s", "m/s", "meter for second", Velocity, 0, 304800);

// To Ft_S
Declare_Conversion(Meter_S, Ft_S, V) { return 3.28083989501312 * V; }

// To Meter_S
Declare_Conversion(Ft_S, Meter_S, V) { return 0.3048 * V; }


# endif
