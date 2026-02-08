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
*/# include <iostream>
# include <algorithm>
# include <cctype>
# include <unordered_map>

# include <ah-stl-utils.H>

# include <uconv.H>
// # include <uconv-list.H> // Removed in favor of generated headers
# include <all_units.H> // Include all generated units to ensure registration

# include <nlohmann/json.hpp> 

using json = nlohmann::json;

namespace
{
  std::string compact_symbol(const std::string & symbol)
  {
    std::string out;
    out.reserve(symbol.size());
    for (unsigned char c : symbol)
      if (not std::isspace(c))
	out.push_back(static_cast<char>(c));
    return out;
  }

  std::string to_lower_ascii(std::string s)
  {
    std::transform(s.begin(), s.end(), s.begin(),
		   [] (unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
  }

  const std::unordered_map<std::string, std::string> &
  unit_symbol_aliases()
  {
    static const std::unordered_map<std::string, std::string> aliases =
      {
	{"s", "sec"},
	{"sec", "sec"},
	{"second", "sec"},
	{"seconds", "sec"},
	{"hr", "h"},
	{"hrs", "h"},
	{"hour", "h"},
	{"hours", "h"},
	{"d", "day"},
	{"day", "day"},
	{"days", "day"},
	{"\xCE\xA9", "ohm"}, // Ω
	{"\xE2\x84\xA6", "ohm"}, // Ω
	{"k\xCE\xA9", "kohm"}, // kΩ
	{"k\xE2\x84\xA6", "kohm"}, // kΩ
	{"M\xCE\xA9", "Mohm"}, // MΩ
	{"M\xE2\x84\xA6", "Mohm"}, // MΩ
	{"m\xCE\xA9", "mohm"}, // mΩ
	{"m\xE2\x84\xA6", "mohm"}, // mΩ
	{"\xCE\xBC" "F", "uF"}, // μF
	{"\xC2\xB5" "F", "uF"}, // µF
	{"\xCE\xBC" "f", "uF"}, // μf
	{"\xC2\xB5" "f", "uF"}, // µf
	{"\xC2\xB0" "C", "degC"}, // °C
	{"\xC2\xB0" "F", "degF"}, // °F
	{"\xC2\xB0" "R", "degR"}, // °R
	{"K", "degK"}
      };
    return aliases;
  }
}

// static void init_unit_converters(); // Removed

// the following data is declared in units.H
UnitItemTable * PhysicalQuantity::tbl = nullptr;

UnitItemTable * Unit::tbl = nullptr;

DynSetTree<const Unit *> * Unit::unit_tbl = nullptr;

static std::size_t fst_unit_pair_hash
(const std::pair<std::pair<const Unit*, const Unit*>, Unit_Convert_Fct_Ptr> & p)
{
  return dft_hash_fct(p.first);
}

static std::size_t snd_unit_pair_hash
(const std::pair<std::pair<const Unit*, const Unit*>, Unit_Convert_Fct_Ptr> & p)
{
  return snd_hash_fct(p.first);
}

UnitMap * __unit_map = nullptr;
CompoundUnitTbl * __compound_unit_tbl = nullptr;

const PhysicalQuantity PhysicalQuantity::null_physical_quantity;

const Unit Unit::null_unit;

const double Unit::Invalid_Value = std::numeric_limits<double>::max();

const VtlQuantity VtlQuantity::null_quantity;

/* The goal of this function is to assure that the tables required by
   the units system are adequately initialized. 

   The technique consists in instantiating the required tables as
   static variables of this constructor. In this way we assure that
   tables are instantiated exactly once time. These static variables
   use the default constructor. Then, on each table the real
   constructor is called through the placement new operator
*/
UnitsInstancer::UnitsInstancer()
{
  static std::size_t count = 0;
  if (count++ > 0)
    return;
  
  static UnitItemTable physicalquantity_tbl;
  static UnitItemTable unit_tbl;
  static DynSetTree<const Unit *> unit_unit_tbl;

  PhysicalQuantity::tbl = &physicalquantity_tbl;
  Unit::tbl = &unit_tbl;
  Unit::unit_tbl = &unit_unit_tbl;

  static UnitMap __unit_map(3500, fst_unit_pair_hash, snd_unit_pair_hash);
  ::__unit_map = &__unit_map;

  static CompoundUnitTbl __compound_unit_tbl;
  ::__compound_unit_tbl = &__compound_unit_tbl;

  // Keep default-initialized null sentinels. Reconstructing them via placement-new
  // here causes LSan-visible leaks in their internal string/list state at shutdown.

  // init_unit_converters(); // Removed
}

bool conversion_exist(const char * src_symbol, const char * tgt_symbol)
{
  return exist_conversion(src_symbol, tgt_symbol);
}

double unit_convert(const char * src_symbol, const char * tgt_symbol,
		    double val)
{
  return unit_convert_symbol_to_symbol(src_symbol, val, tgt_symbol);
}

static json to_json(const Unit * unit_ptr)
{
  json j;
  j["name"] = unit_ptr->name;
  j["description"] = unit_ptr->description;
  j["symbol"] = unit_ptr->symbol;
  j["latex_symbol"] = unit_ptr->latex_symbol;
  j["minimum_value"] = unit_ptr->min_val;
  j["maximum_value"] = unit_ptr->max_val;
  j["epsilon"] = unit_ptr->get_epsilon();
  return j;
}

static json to_json(const PhysicalQuantity * const pq)
{
  json j;
  j["name"] = pq->name;
  j["description"] = pq->description;
  j["symbol"] = pq->symbol;
  j["latex_symbol"] = pq->latex_symbol;
  j["units"] =
    to_vector(pq->units().maps<json>([] (auto p) { return to_json(p); }));
  
  return j;
}

std::string units_json()
{
  json j;
  j["uconv_physical_quantities"] =
    to_vector(PhysicalQuantity::quantities().maps<json>([] (auto p)
    { return to_json(p); }));
  return j.dump(2);
}

const UnitsInstancer & units_instance = UnitsInstancer::init();

std::string Unit::normalize_lookup_token(const std::string & token)
{
  auto it = token.begin();
  auto et = token.end();
  while (it != et and std::isspace(static_cast<unsigned char>(*it)))
    ++it;
  while (it != et and std::isspace(static_cast<unsigned char>(*(et - 1))))
    --et;

  return std::string(it, et);
}

std::string Unit::normalize_symbol_alias(const std::string & symbol)
{
  const std::string compacted = compact_symbol(symbol);
  if (compacted.empty())
    return compacted;

  const auto & aliases = unit_symbol_aliases();
  if (const auto it = aliases.find(compacted); it != aliases.end())
    return it->second;

  const std::string lower = to_lower_ascii(compacted);
  if (const auto it = aliases.find(lower); it != aliases.end())
    return it->second;

  return compacted;
}

// The following global singleton variables are generated by extract-cv script and concatenated to this file
