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
*/# ifndef ANGLE_UNIT_H
# define ANGLE_UNIT_H

# include <cmath>
# include "uconv.H"

Declare_Physical_Quantity(Angle, "angle", "\\angle",
			  "figure formed by two rays sharing a common endpoint");

Declare_Unit(Degree, "deg", "\\degree", "Angle measured in Degrees", Angle, -90, 90);
Declare_Unit(Radian, "rad", "rad", "Angle measured in Radians", Angle, -1.5707963267948966, 1.5707963267948966);

Declare_Conversion(Degree, Radian, val) { return val*M_PI/180; }
Declare_Conversion(Radian, Degree, val) { return val*180/M_PI; }

# endif
