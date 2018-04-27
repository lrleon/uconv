
/*
   _   _  ___ ___  _ ____   __
  | | | |/ __/ _ \| '_ \ \ / /  Physical magnitudes and units conversion
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
/* 
  This file is part of uconv library

  Copyright (c) 2018 Leandro Rabindranath Leon

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see
  <https://www.gnu.org/licenses/>.
*/

# include <istream>

# include <tclap/CmdLine.h>
# include <uconv-list.H>

using namespace TCLAP;

CmdLine cmd = { "vector-conversion", ' ', "0" };

ValueArg<string> source = {"S", "source-unit", "source unit", true,
			   "", "source unit", cmd};
ValueArg<string> target = {"T", "target-unit", "target unit", true,
			   "", "target unit", cmd};

UnlabeledMultiArg<double> vals = { "values", "list of values to convert", true,
				   "list of values to convert", cmd };

const Unit * search_unit(const string & name)
{
  auto unit_ptr = Unit::search_by_name(name);
  if (unit_ptr == nullptr)
    {
      unit_ptr = Unit::search_by_symbol(name);
      if (unit_ptr == nullptr)
	{
	  cout << "Unit " << name << " not found" << endl;
	  abort();
	}
    }
  return unit_ptr;
}

void convert()
{
  auto src_unit = search_unit(source.getValue());
  auto tgt_unit = search_unit(target.getValue());
  auto convert_fct = search_conversion(*src_unit, *tgt_unit);

  for (auto v : vals)
    cout << (*convert_fct)(v) << " ";
  cout << endl;
}

int main(int argc, char *argv[])
{
  cmd.parse(argc, argv);
  convert();
}
