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
*//* 
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

# include <gsl/gsl_rng.h>
# include <ctime>
# include <cmath>
# include <memory>
# include <algorithm>

# include <tclap/CmdLine.h>

# include <ahFunctional.H>
# include <ah-errors.H>
# include <ah-string-utils.H>
# include <ah-stl-utils.H>
# include <htlist.H>

# include <uconv-list.H>
# include <ah-uconv-errors.H>

using namespace TCLAP;
using namespace Aleph;

std::size_t precision = 6;

DynList<std::string>
generate_row(const Unit & unit, double val, double epsilon, bool verbose)
{
  DynList<std::string> conversions;
  
  VtlQuantity q(unit);
  try
    {
      if (verbose)
	std::cout << "    sample = " << val << " (" << unit.symbol << ")" << std::endl;
      q = VtlQuantity(unit, val);
      if (verbose)
	std::cout << "    Instantiated = " << q << std::endl;
    }
  catch (std::exception & e)
    {
      std::cout << "Error with generated sample" << val << std::endl
	   << e.what() << std::endl
	   << "Sample " << val << " is not inside [" << unit.min_val
	   << ", " << unit.max_val << "]" << std::endl;
      abort();
    }
  
  for (auto ut = unit.family_units().get_it(); ut.has_curr(); ut.next())
    {
      const Unit * const unit_ptr = ut.get_curr();
      VtlQuantity conv(*unit_ptr);
      try
	{
	  if (verbose)
	    std::cout << "        Converting " << q << " to "
		 << unit_ptr->symbol << std::endl;
	  conv = VtlQuantity(*unit_ptr, q); // conversion
	  if (verbose)
	    std::cout << "        done = " << conv << std::endl;
	}
      catch (std::exception & e)
	{
	  std::cout << "Error " << q << " to " << unit_ptr->name << std::endl
	       << e.what() << std::endl;
	  abort();
	}

      if (verbose)
	std::cout << "        Returning to " << unit.symbol << std::endl;
      VtlQuantity inv = { unit, conv };
      if (verbose)
	std::cout << "        done = " << inv << std::endl
	     << std::endl;
      ah_range_error_if(std::abs(q.get_value() - inv.get_value()) > epsilon)
	<< "Conversion for value " << val << " from unit "
	<< unit.name << " to unit " << unit_ptr->name
	<< " does not satisfy epsilon threshold " << epsilon << std::endl
	<< "Original value     = " << q << std::endl
	<< "Intermediate value = " << conv << std::endl
	<< "Returned value = " << inv << std::endl;

      conversions.append(to_string(conv.get_value(), precision));
    }

  return conversions;
}

DynList<DynList<std::string>>
test_extremes_conversions(const PhysicalQuantity & pq, bool verbose,
			  double max_range, double epsilon)
{
      // only the units related to physical quantity pq
  auto units = pq.units();
  if (verbose)
    std::cout << std::endl
	 << "Testing with extremes" << std::endl
	 << std::endl;

  DynList<DynList<std::string>> rows;
      // generate the rows
  for (auto it = units.get_it(); it.has_curr(); it.next())
    {
      auto unit_ptr = it.get_curr();
      const double min = unit_ptr->min_val;
      const double urange = std::min(unit_ptr->max_val - min, max_range);
      const double max = min + urange;

      DynList<std::string> conversions;
      conversions.append(generate_row(*unit_ptr, min, epsilon, verbose));
      conversions.append(generate_row(*unit_ptr, max, epsilon, verbose));

      DynList<std::string> row;
      row.append(unit_ptr->name);
      row.append(std::to_string(min));
      row.append(std::to_string(max));
      row.append(conversions);

      rows.append(row);
    }

      // generate title row
  DynList<std::string> title = { "Unit name" };
  DynList<std::string> vals = { "min", "max" };
  title.append(vals);

  for (auto it = vals.get_it(); it.has_curr(); it.next())
    {
      const std::string & val = it.get_curr();
      for (auto uit = units.get_it(); uit.has_curr(); uit.next())
	{
	  const std::string name = val + "-" + uit.get_curr()->symbol;
	  title.append(name);
	}
    }

  DynList<DynList<std::string>> ret = { std::move(title) } ;
  ret.append(rows);

  return ret;
}


DynList<DynList<std::string>>
test_random_conversions(const PhysicalQuantity & pq, bool verbose,
			const std::size_t nsamples, double max, double epsilon,
			gsl_rng * r)
{
  using Puv = std::pair<const Unit * const, DynList<double>>;

      // only the units related to physical quantity pq
  auto units = pq.units();

  if (verbose)
    std::cout << "Generating random samples " << std::endl;

      // generate the random samples
  auto samples = units.maps<Puv>([nsamples, r, max, verbose] (auto unit_ptr)
    {
      if (verbose)
	std::cout << "    For " << unit_ptr->name << ":";
      auto min = unit_ptr->min_val;
      auto urange = unit_ptr->max_val - min;
      urange = std::min(urange, max);
      DynList<double> values;
      for (std::size_t i = 0; i < nsamples; ++i)
	{
	  auto val = min + urange*gsl_rng_uniform(r);
	  values.append(val);
	  if (verbose)
	    std::cout << " " << val;
	}
      if (verbose)
	std::cout << std::endl;
      
      return std::make_pair(unit_ptr, std::move(values));
    });

  if (verbose)
    std::cout << std::endl
	 << "Testing " << std::endl
	 << std::endl;

      // generate the rows
  auto rows = samples.maps<DynList<std::string>>([epsilon, verbose] (Puv p)
    {
      DynList<std::string> conversions;
      const DynList<double> & samples = p.second;
      for (auto it = samples.get_it(); it.has_curr(); it.next())
	conversions.append(generate_row(*p.first, it.get_curr(),
					epsilon, verbose));
      
      DynList<std::string> ret;
      ret.append(p.first->name);
      ret.append(samples.maps<std::string>([] (auto v) { return std::to_string(v); }));
      ret.append(conversions);

      return ret;
    });

      // generate title row
  DynList<std::string> title = { "Unit name" };
  DynList<std::string> vals = range(nsamples).maps<std::string>([] (auto i)
                         { return "sample-" + std::to_string(i); });
  title.append(vals);

  for (auto it = vals.get_it(); it.has_curr(); it.next())
    {
      const std::string & val = it.get_curr();
      for (auto uit = units.get_it(); uit.has_curr(); uit.next())
	{
	  const std::string name = val + "-" + uit.get_curr()->symbol;
	  title.append(name);
	}
    }

  DynList<DynList<std::string>> ret = { std::move(title) } ;
  ret.append(rows);

  return ret;
}

struct Epsilon
{
  std::string symbol;
  double epsilon;

  Epsilon & operator = (const std::string & str)
  {
    std::istringstream iss(str);
    ah_tclap_arg_parse_error_unless(iss >> symbol >> epsilon)
      << str << " is not a pair unit-symbol epsilon";

    return *this;
  }

  friend std::ostream& operator << (std::ostream &os, const Epsilon & a) 
  {
    return os << a.symbol << " " << a.epsilon;
  }
  
  std::ostream& print(std::ostream &os) const
  {
    return os << *this;
  }
};

namespace TCLAP
{
  template<> struct ArgTraits<Epsilon> { typedef StringLike ValueCategory; };
}

int main(int argc, char *argv[])
{
  CmdLine cmd(argv[0], ' ', "0");

  ValueArg<std::size_t> nsamples = { "n", "num-samples",
				"number of random samples", false,
				3, "number of samples", cmd };

  ValueArg<double> m = { "m", "max", "maximum range of a unit", false, 1000,
			 "maximum range of a unit", cmd };

  unsigned long dft_seed = std::time(nullptr);
  ValueArg<unsigned long> seed = { "s", "seed",
				   "seed for random number generator",
				   false, dft_seed, "random seed", cmd };

  SwitchArg csv("c", "csv", "output in csv format", cmd, false);

  ValueArg<double> epsilon("E", "Epsilon",
			   "precision threshold for numeric comparaisons",
			   false, 1e-4, "precision threshold", cmd);

  MultiArg<Epsilon> epsilons("e", "epsilon",
			     "epsilon of form \"unit-symbol epsilon\"",
			     false, "epsilon threshold", cmd);

  std::vector<std::string> pq = to_vector(PhysicalQuantity::names());
  PhysicalQuantity::quantities().for_each([&pq] (auto p)
					  { pq.push_back(p->name); });
				ValuesConstraint<std::string> allowed(pq);
  ValueArg<std::string> pm = { "Q", "physical-quantity", "name of physical quantity",
			  false, "", &allowed, cmd };

  SwitchArg extremes = { "x", "extremes", "test units extremes", cmd, false};

  SwitchArg print = { "p", "print", "print units", cmd, false };

  SwitchArg print_pq =
    { "P", "print-pq", "print physical quantities", cmd, false };

  SwitchArg ver = { "v", "verbose", "verbose mode", cmd, false };

  ValueArg<std::size_t> d = { "d", "digits", "number of digits", false, 10,
			 "number of digits", cmd };

  cmd.parse(argc, argv);

  if (print_pq.getValue())
    {
      PhysicalQuantity::names().for_each([] (const std::string & name)
        {
	  std::cout << name << std::endl;
	});
      exit(0);
    }
				
  if (not pm.isSet())
    {
      std::cout << "PARSE ERROR:" << std::endl
	   << "             Required argument missing: physical-quantity"
	   << std::endl;
      abort();
    }

  auto verbose = ver.getValue();

  std::unique_ptr<gsl_rng, decltype(gsl_rng_free)*>
    r(gsl_rng_alloc(gsl_rng_mt19937), gsl_rng_free);
  gsl_rng_set(r.get(), seed.getValue() % gsl_rng_max(r.get()));

  auto ptr = PhysicalQuantity::search(pm.getValue());
  if (ptr == nullptr)
    {
      std::cout << "Physical quantity " << pm.getValue() << " not found " << std::endl;
      abort();
    }

  auto p = check_conversions(*ptr);
  if (not p.first)
    {
      std::cout << "Missing conversions: " << std::endl;
      p.second.for_each([] (auto s) { std::cout << "    " << s << std::endl; });
      abort();
    }

  for (auto ep : epsilons.getValue())
    {
      auto unit_ptr = Unit::search_by_symbol(ep.symbol);
      if (unit_ptr == nullptr)
	{
	  std::cout << "In epsilon specification: unit symbol " << ep.symbol
	       << " not found" << std::endl;
	  abort();
	}

      if (ep.epsilon <= 0 or ep.epsilon >= 1)
	{
	  std::cout << "In epsilon specification of unit" << unit_ptr->name
	       << " (" << ep.symbol << "): value " << ep.epsilon
	       << " is not inside the range (0, 1)" << std::endl;
	  abort();
	}
      unit_ptr->set_epsilon(ep.epsilon);
    }

  if (print.getValue())
    {
      std::cout << ptr->to_string(60) << std::endl;
      ptr->units().for_each([] (auto u)
			    {
			      std::cout << *u << std::endl
				   << std::endl;
			    });
    }

  if (d.isSet())
    precision = d.getValue();

  DynList<DynList<std::string>> mat;
  if (extremes.getValue())
    mat = test_extremes_conversions(*ptr, verbose,
				    m.getValue(), epsilon.getValue());
  else
    mat = test_random_conversions(*ptr, verbose, nsamples.getValue(),
				  m.getValue(), epsilon.getValue(), r.get());
  
  std::cout << "Seed = " << seed.getValue() << std::endl;

  if (csv.getValue())
    std::cout << to_string(format_string_csv(mat)) << std::endl;
  else
    std::cout << to_string(format_string(mat)) << std::endl;

  return 0;
}
