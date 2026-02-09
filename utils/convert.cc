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

const Unit * search_unit(const std::string & name)
{
  auto unit_ptr = Unit::search_by_name(name);
  if (unit_ptr == nullptr)
    {
      unit_ptr = Unit::search_by_symbol(name);
      if (unit_ptr == nullptr)
	{
	  std::cout << "Unit " << name << " not found" << std::endl;
	  abort();
	}
    }
  return unit_ptr;
}

void convert(const Unit * src_unit, const Unit * tgt_unit, std::istream & in)
{
  double val;
  while (in >> val)
    std::cout << unit_convert(*src_unit, val, *tgt_unit) << " ";
  std::cout << std::endl;
}

void list_all_units()
{
  DynList<DynList<std::string>> rows;
  PhysicalQuantity::quantities().for_each([&rows] (auto & pq)
    {
      rows.append(pq->units().template maps<DynList<std::string>>([&pq] (auto p)
        {
	  return DynList<std::string>({ pq->name, pq->symbol, pq->latex_symbol,
		p->name, p->symbol, p->latex_symbol });
	}));
    });
  rows.insert({"Physical-Quantity", "symbol", "LaTeX symbol", "Unit name",
	"Unit symbol", "LaTeX symbol"});
  std::cout << to_string(format_string(rows)) << std::endl;
  exit(0);
}

void ruby_hash()
{
  std::cout << "{" << std::endl;
  Unit::units().for_each([] (const Unit * ptr)
    {
      std::cout << "  '" << ptr->name << "' => '" << ptr->symbol << "'," << std::endl;
    });
  std::cout << "}" << std::endl;
  exit(0);
}

void list_sibling_units(const Unit & unit)
{
  DynList<DynList<std::string>> rows = unit.family_units().maps<DynList<std::string>>
    ([] (auto ptr)
     {
       return DynList<std::string>({ptr->name, ptr->symbol, ptr->latex_symbol});
     });
  rows.insert({"name", "symbol", "LaTeX symbol"});
  std::cout << to_string(format_string(rows)) << std::endl;
  exit(0);
}

CmdLine cmd("conversion", ' ', "0");

// Helper to build units std::vector avoiding flatten issues
std::vector<std::string> build_units_vector() {
    DynList<std::string> all_unit_strings;
    Unit::units().for_each([&all_unit_strings](auto u) {
        all_unit_strings.append(u->name);
        all_unit_strings.append(u->symbol);
    });
    return to_vector(all_unit_strings);
}

std::vector<std::string> units = build_units_vector();
  
ValuesConstraint<std::string> allowed(units);
ValueArg<std::string> unit = { "u", "unit-symbol", "symbol of unit",
			  false, "", &allowed, cmd };

MultiArg<std::string> unit_desc = { "U", "Unit-symbol", "describe unit",
			       false, &allowed, cmd };

std::vector<std::string> pqs =
	  to_vector(PhysicalQuantity::quantities().maps<std::string>([] (auto p)
  { return p->name; }));
ValuesConstraint<std::string> pq_allowed(pqs);
ValueArg<std::string> unit_list = { "L", "list-units",
			       "list units associated to a physical quantity",
			       false, "", &pq_allowed, cmd };

ValueArg<double> sample_val = {"s", "sample", "sample", false, 0, "sample", cmd};

ValueArg<std::string> source = {"S", "source-unit", "source unit", false,
			   "", "source unit", cmd};
ValueArg<std::string> target = {"T", "target-unit", "target unit", false,
			   "", "target unit", cmd};

SwitchArg l = { "l", "list", "list all units", cmd, false };

SwitchArg v("v", "verbose", "verbose mode", cmd, false);

SwitchArg json("j", "json", "json list of units", cmd, false);

SwitchArg ruby("r", "ruby", "ruby list of units", cmd, false);

ValueArg<std::string> file = { "f", "file", "input file name", false, "",
			  "input file name", cmd };

SwitchArg in_pipe = { "p", "pipe", "input by std::cin", cmd };

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
	  std::cout << "Physical quantity " << pq_name << " not found" << std::endl;
	  abort();
	}
      pq->units().for_each([] (auto uptr) { std::cout << uptr->name << std::endl; });
      exit(0);
    }

  if (json.isSet())
    {
      std::cout << units_json() << std::endl;
      exit(0);
    }

  auto verbose = v.getValue();

  if (unit_desc.isSet())
    {
      for (const auto & s : unit_desc.getValue())
	std::cout << Unit::search_by_symbol(s)->to_string(50, 2) << std::endl
	     << std::endl;
      exit(0);
    }

  if (source.isSet() and target.isSet())
    {
      auto src_ptr = search_unit(source.getValue());
      auto tgt_ptr = search_unit(target.getValue());

      if (file.isSet() or in_pipe.getValue())
	{
	  if (in_pipe.isSet())
	    convert(src_ptr, tgt_ptr, std::cin);
	  else
	    {
	      std::ifstream in(file.getValue());
	      if (not in.good())
		{
		  std::cout << "Cannot open " << file.getValue() << std::endl;
		  abort();
		}
	      convert(src_ptr, tgt_ptr, in);
	    }
	  exit(0);
	}

      VtlQuantity val(*src_ptr, sample_val.getValue());
      std::cout << VtlQuantity(*tgt_ptr, val).raw() << std::endl;
      exit(0);
    }

  if (not unit.isSet() and not sample_val.isSet())
    {
      std::cout << "Flags -u and -s must be set" << std::endl;
      abort();
    }

  auto unit_ptr = search_unit(unit.getValue());
  if (unit_ptr == nullptr)
    {
      std::cout << "Unit symbol " << unit.getValue() << " not found" << std::endl;
      abort();
    }

  std::cout << *unit_ptr << std::endl
       << std::endl
       << "Conversions:" << std::endl
       << std::endl;

  VtlQuantity val(*unit_ptr, sample_val.getValue());

  for (auto u : Unit::units(unit_ptr->physical_quantity))
    {
      if (verbose)
	std::cout << "    " << val << " to " << u->symbol << std::endl;
      if (exist_conversion(*unit_ptr, *u))
	std::cout << "    " << val << " = " << VtlQuantity(*u, val) << std::endl;
      else
	std::cout << "    "  << val << " = "
	     << "WARNING: there is no conversion from " << unit_ptr->symbol
	     << " to " << u->symbol << std::endl;
    }
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  test(argc, argv);
  return 0;
}
