
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
#ifndef FLOWRATE_UNIT_H
#define FLOWRATE_UNIT_H

# include "uconv.H"

Declare_Physical_Quantity(FlowRate, "Q", "Q",
			  "Volume rate of some fluid flow that is transported "
			  "through a given cross-sectional area");

Declare_Unit(BPD, "bpd", "bpd",
	     "Volume rate measured in barrels per day", FlowRate, 0, 1e10);

Declare_Unit(GPM, "gpm", "gpm",
	     "Volume rate measured in U.S. Gallon Per Minute",
	     FlowRate, 0, 291666666.667);

Declare_Unit(CMD, "cmd", "cmd",
	     "Volume rate measured in cubic meter per day", FlowRate, 0, 1589872949.28);

Declare_Unit(CMS, "cms", "cms",
	     "Volume rate measured in cubic meter per second",
	     FlowRate, 0, 18401.3072833);

// to BPD 
Declare_Conversion(GPM, BPD, V) { return 34.2857142857 * V; }
Declare_Conversion(CMD, BPD, V) { return 6.28981077043 * V; }
Declare_Conversion(CMS, BPD, V) { return 543439.650565* V; }

// to GPM 
Declare_Conversion(BPD, GPM, V) { return 2.91666666667e-2 * V; }
Declare_Conversion(CMD, GPM, V) { return 0.183452814138 * V; }
Declare_Conversion(CMS, GPM, V) { return 15850.3231415 * V; }

// to CMD
Declare_Conversion(BPD, CMD, V) { return 0.158987294928 * V; }
Declare_Conversion(GPM, CMD, V) { return 5.45099296896 * V; }
Declare_Conversion(CMS, CMD, V) { return 86400 * V; }

// to CMS 
Declare_Conversion(BPD, CMS, V) { return 1.84013072833e-6 * V; }
Declare_Conversion(CMD, CMS, V) { return 1.15740740741e-5  * V; }
Declare_Conversion(GPM, CMS, V) { return 0.0000630901964 * V; }

#endif
