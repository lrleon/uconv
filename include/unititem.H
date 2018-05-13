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
/*
  Basic bookkeeping for uconv unit library
 */
# ifndef DESC_TABLE_H
# define DESC_TABLE_H

# include <memory>
# include <sstream>
# include <string>

# include <ah-string-utils.H>
# include <tpl_dynMapTree.H>

/** This is a basic descriptor used for physical quantities and units.

   @author Leandro Rabindranath Leon
 */
struct UnitItem
{
  friend class PhysicalQuantity;
  friend class Unit;

  const std::string name         = "Undefined";
  const std::string symbol       = "Undefined";
  const std::string description  = "Undefined";
  const std::string latex_symbol = "Undefined";

private:

  UnitItem() {}

public:

  UnitItem(const std::string & __name, const std::string & __symbol,
	   const std::string & desc) noexcept
    : name(__name), symbol(__symbol), description(desc)
  {
    // empty
  }

  UnitItem(const std::string & name, const std::string & symbol,
	   const std::string & latex_symbol,
	   const std::string & desc) noexcept
    : name(name), symbol(symbol), description(desc), latex_symbol(latex_symbol)
  {
    // empty
  }

  string to_string() const
  {
    ostringstream s;
    s << "UnitItem name = " << name << endl
      << "Symbol        = " << symbol << endl
      << "Description   = " << description;
    return s.str();
  }

  string to_string(size_t width, size_t left_margin = 0) const
  {
    const string margin(left_margin, ' ');
    ostringstream s;
    s << margin << "UnitItem name = " << name << endl
      << margin << "Symbol        = " << symbol << endl
      << margin << "Description   = "
      << align_text_to_left_except_first(description, width, 16);
    return s.str();
  }

  friend ostream & operator << (ostream & out, const UnitItem & ui)
  {
    return out << ui.to_string();
  }
};

/** Basic table storing physical quantities and unit descriptors.

    @author Leandro Rabindranath Leon
 */
class UnitItemTable
{
  DynMapTree<std::string, const UnitItem *> name_tbl; // index by unit
  DynMapTree<std::string, const UnitItem *> symbol_tbl; // index by symbol

public:

  /// Return all the stored descriptors.
  DynList<const UnitItem *> items() const
  {
    return name_tbl.values();
  }

  /// Return all the stored descriptor names.
  DynList<string> names() const { return name_tbl.keys(); }

  DynList<string> symbols() const { return symbol_tbl.keys(); }

  /// Return an iterator to a list of pair<string, const UnitItem*>
  /// items. First item is the descriptor name and the second one is a
  /// pointer to the descriptor.
  auto get_it() { return name_tbl.get_it(); }

  /** Register a new descriptor.

      @param[in] ptr pointer to the descriptor. It must correctly allocated.
      @throw bad_alloc if there is no enough memory.
      @throw domain_error if it already exists a descriptor with the
      same name or the same symbol.
   */
  void register_item(const UnitItem * ptr)
  {
    if (name_tbl.contains(ptr->name))
      {
	ostringstream s;
	s << " name " << ptr->name << " already exist";
	throw domain_error(s.str());
      }

    if (symbol_tbl.contains(ptr->symbol))
      {
	ostringstream s;
	s << "unit symbol " << ptr->symbol << " already exist";
	throw domain_error(s.str());
      }
    
    name_tbl.insert(ptr->name, ptr);
    symbol_tbl.insert(ptr->symbol, ptr);
  }

  /// Return true if the table contains a descriptor with name `name`.
  bool exists_name(const string & name) const noexcept
  {
    return name_tbl.contains(name);
  }

  /// Return true if the table contains a descriptor with symbol `symbol`.
  bool exists_symbol(const string & symbol) const noexcept
  {
    return symbol_tbl.contains(symbol);
  }

  /// Return a pointer to the descriptor containing the name `name` if
  /// this exists; otherwise, it returns `nullptr`
  const UnitItem * search_by_name(const string & name) const noexcept
  {
    auto p = name_tbl.search(name);
    return p ? p->second : nullptr;
  }

  /// Return a pointer to the descriptor containing the symbol `symbol` if
  /// this exists; otherwise, it returns `nullptr`
  const UnitItem * search_by_symbol(const string & symbol) const noexcept
  {
    auto p = symbol_tbl.search(symbol);
    return p ? p->second : nullptr;
  }

  /// Return the number of descriptors stored.
  size_t size() const noexcept { return name_tbl.size(); }

  /// Throw `domain_error` exception if the descriptor pointed by
  /// `ptr` already contains the string `str` as name or symbol. It is
  /// a helper validation function.
  void validate(const UnitItem * ptr, const string & str)
  {
    {
      const string & name = ptr->name;
      if (exists_name(str))
	{
	  ostringstream s;
	  s << "Repeated " << str << " name " << name;
	  throw domain_error(s.str());
	}
    }

    {
      const string & symbol = ptr->symbol;
      if (exists_symbol(str))
	{
	  ostringstream s;
	  s << "Repeated " << str << " symbol " << symbol;
	  throw domain_error(s.str());
	}
    }
  }
};


# endif // DESC_TABLE_H
