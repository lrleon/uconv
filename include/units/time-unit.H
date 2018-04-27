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
*/# ifndef TIME_UNIT_H
# define TIME_UNIT_H

# include "uconv.H"

Declare_Physical_Quantity(Time, "t", "t",
			  "The mythical and mysterious fourth dimension");

Declare_Unit(day, "day", "d", "twenty four hours", Time, 0, 365*24);
Declare_Unit(hour, "h", "h", "sixty minutes", Time, 0, 10*365*24);
Declare_Unit(minute, "min", "min", "sixty seconds", Time, 0, 10*365*24*60);
Declare_Unit(second, "sec", "seconds", "VIRGINIA", Time, 0, 10*365*24*60*60);

Declare_Conversion(day, hour, val) { return 24*val; }
Declare_Conversion(day, minute, val) { return 24*60*val; }
Declare_Conversion(day, second, val) { return 24*60*60*val; }

Declare_Conversion(hour, day, val) { return val/24; }
Declare_Conversion(hour, minute, val) { return 60*val; }
Declare_Conversion(hour, second, val) { return 60*60*val; }

Declare_Conversion(minute, day, val) { return val/(24*60); }
Declare_Conversion(minute, hour, val) { return val/60; }
Declare_Conversion(minute, second, val) { return 60*val; }

Declare_Conversion(second, day, val) { return val/(24*60*60); }
Declare_Conversion(second, hour, val) { return val/(60*60); }
Declare_Conversion(second, minute, val) { return val/60; }

# endif
