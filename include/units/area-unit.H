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
*/# ifndef AREA_UNIT_H
# define AREA_UNIT_H

# include <uconv.H>

Declare_Physical_Quantity(Area, "A", "A",
			  "extent of a two-dimensional figure or shape")

Declare_Unit(Feet2, "ft2", "ft2", "feet square", Area, 0, 1e7);

Declare_Unit(Inch2, "in2", "in2", "inch square", Area, 0, 12*1e7);

Declare_Conversion(Feet2, Inch2, a) { return a/12; }
Declare_Conversion(Inch2, Feet2, a) { return 12*a; }


# endif
