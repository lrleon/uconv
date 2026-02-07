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
# include <istream>

# include <ah-stl-utils.H>

# include <tclap/CmdLine.h>
# include <uconv-list.H>

using namespace TCLAP;

UnitsInstancer init;

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

void convert(const Unit * src_unit, const Unit * tgt_unit, istream & in)
{
  double val;
  while (in >> val)
    cout << unit_convert(*src_unit, val, *tgt_unit) << " ";
  cout << endl;
}

void list_all_units()
{
  DynList<DynList<string>> rows;
  PhysicalQuantity::quantities().for_each([&rows] (auto & pq)
    {
      rows.append(pq->units().template maps<DynList<string>>([&pq] (auto p)
        {
	  return DynList<string>({ pq->name, pq->symbol, pq->latex_symbol,
		p->name, p->symbol, p->latex_symbol });
	}));
    });
  rows.insert({"Physical-Quantity", "symbol", "LaTeX symbol", "Unit name",
	"Unit symbol", "LaTeX symbol"});
  cout << to_string(format_string(rows)) << endl;
  exit(0);
}

void ruby_hash()
{
  cout << "{" << endl;
  Unit::units().for_each([] (const Unit * ptr)
    {
      cout << "  '" << ptr->name << "' => '" << ptr->symbol << "'," << endl;
    });
  cout << "}" << endl;
  exit(0);
}

void list_sibling_units(const Unit & unit)
{
  DynList<DynList<string>> rows = unit.family_units().maps<DynList<string>>
    ([] (auto ptr)
     {
       return DynList<string>({ptr->name, ptr->symbol, ptr->latex_symbol});
     });
  rows.insert({"name", "symbol", "LaTeX symbol"});
  cout << to_string(format_string(rows)) << endl;
  exit(0);
}

CmdLine cmd("conversion", ' ', "0");

// Helper to build units vector avoiding flatten issues
vector<string> build_units_vector() {
    DynList<string> all_unit_strings;
    Unit::units().for_each([&all_unit_strings](auto u) {
        all_unit_strings.append(u->name);
        all_unit_strings.append(u->symbol);
    });
    return to_vector(all_unit_strings);
}

vector<string> units = build_units_vector();
  
ValuesConstraint<string> allowed(units);
ValueArg<string> unit = { "u", "unit-symbol", "symbol of unit",
			  false, "", &allowed, cmd };

MultiArg<string> unit_desc = { "U", "Unit-symbol", "describe unit",
			       false, &allowed, cmd };

vector<string> pqs =
	  to_vector(PhysicalQuantity::quantities().maps<string>([] (auto p)
  { return p->name; }));
ValuesConstraint<string> pq_allowed(pqs);
ValueArg<string> unit_list = { "L", "list-units",
			       "list units associated to a physical quantity",
			       false, "", &pq_allowed, cmd };

ValueArg<double> sample_val = {"s", "sample", "sample", false, 0, "sample", cmd};

ValueArg<string> source = {"S", "source-unit", "source unit", false,
			   "", "source unit", cmd};
ValueArg<string> target = {"T", "target-unit", "target unit", false,
			   "", "target unit", cmd};

SwitchArg l = { "l", "list", "list all units", cmd, false };

SwitchArg v("v", "verbose", "verbose mode", cmd, false);

SwitchArg json("j", "json", "json list of units", cmd, false);

SwitchArg ruby("r", "ruby", "ruby list of units", cmd, false);

ValueArg<string> file = { "f", "file", "input file name", false, "",
			  "input file name", cmd };

SwitchArg in_pipe = { "p", "pipe", "input by cin", cmd };

void test(int argc, char *argv[])
{
  cmd.parse(argc, argv);

  if (l.getValue())
    if (not unit.isSet())
      list_all_units();
    else
      list_sibling_units(*search_unit(unit.getValue()));

  if (ruby.getValue())
    ruby_hash();

  if (unit_list.isSet())
    {
      auto pq_name = unit_list.getValue();
      auto pq = PhysicalQuantity::search(pq_name);
      if (pq == nullptr)
	{
	  cout << "Physical quantity " << pq_name << " not found" << endl;
	  abort();
	}
      pq->units().for_each([] (auto uptr) { cout << uptr->name << endl; });
      exit(0);
    }

  if (json.isSet())
    {
      cout << units_json() << endl;
      exit(0);
    }

  auto verbose = v.getValue();

  if (unit_desc.isSet())
    {
      for (const auto & s : unit_desc.getValue())
	cout << Unit::search_by_symbol(s)->to_string(50, 2) << endl
	     << endl;
      exit(0);
    }

  if (source.isSet() and target.isSet())
    {
      auto src_ptr = search_unit(source.getValue());
      auto tgt_ptr = search_unit(target.getValue());

      if (file.isSet() or in_pipe.getValue())
	{
	  if (in_pipe.isSet())
	    convert(src_ptr, tgt_ptr, cin);
	  else
	    {
	      ifstream in(file.getValue());
	      if (not in.good())
		{
		  cout << "Cannot open " << file.getValue() << endl;
		  abort();
		}
	      convert(src_ptr, tgt_ptr, in);
	    }
	  exit(0);
	}

      VtlQuantity val(*src_ptr, sample_val.getValue());
      cout << VtlQuantity(*tgt_ptr, val).raw() << endl;
      exit(0);
    }

  if (not unit.isSet() and not sample_val.isSet())
    {
      cout << "Flags -u and -s must be set" << endl;
      abort();
    }

  auto unit_ptr = search_unit(unit.getValue());
  if (unit_ptr == nullptr)
    {
      cout << "Unit symbol " << unit.getValue() << " not found" << endl;
      abort();
    }

  cout << *unit_ptr << endl
       << endl
       << "Conversions:" << endl
       << endl;

  VtlQuantity val(*unit_ptr, sample_val.getValue());

  for (auto u : Unit::units(unit_ptr->physical_quantity))
    {
      if (verbose)
	cout << "    " << val << " to " << u->symbol << endl;
      if (exist_conversion(*unit_ptr, *u))
	cout << "    " << val << " = " << VtlQuantity(*u, val) << endl;
      else
	cout << "    "  << val << " = "
	     << "WARNING: there is no conversion from " << unit_ptr->symbol
	     << " to " << u->symbol << endl;
    }
  cout << endl;
}

int main(int argc, char *argv[])
{
  test(argc, argv);
  return 0;
}
