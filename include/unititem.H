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
/** @file unititem.H
    @brief Basic bookkeeping structures for the uconv unit library.

    This file defines the `UnitItem` struct and `UnitItemTable` class, which are
    fundamental for storing metadata about physical quantities and units, such as
    names, symbols, and descriptions.

    @author Leandro Rabindranath Leon
    @ingroup Units
*/
# ifndef DESC_TABLE_H
# define DESC_TABLE_H

# include <memory>
# include <sstream>
# include <string>
# include <iostream>
# include <stdexcept>

# include <ah-errors.H>
# include <ah-string-utils.H>
# include <tpl_dynMapTree.H>


/** This is a basic descriptor used for physical quantities and units.

    It stores essential information like the name, symbol, LaTeX representation,
    and a textual description.

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
struct UnitItem
{
  friend class PhysicalQuantity;
  friend class Unit;

  const std::string name         = "Undefined"; ///< The full name of the item (e.g., "meter").
  const std::string symbol       = "Undefined"; ///< The symbol of the item (e.g., "m").
  const std::string description  = "Undefined"; ///< A textual description.
  const std::string latex_symbol = "Undefined"; ///< The LaTeX representation of the symbol.

private:

  UnitItem() {}

public:

  /** Constructor with name, symbol, and description.

      @param[in] __name The full name.
      @param[in] __symbol The symbol.
      @param[in] desc The description.
  */
  UnitItem(const std::string & __name, const std::string & __symbol,
	   const std::string & desc) noexcept
    : name(__name), symbol(__symbol), description(desc)
  {
    // empty
  }

  /** Constructor with name, symbol, LaTeX symbol, and description.

      @param[in] name The full name.
      @param[in] symbol The symbol.
      @param[in] latex_symbol The LaTeX representation of the symbol.
      @param[in] desc The description.
  */
  UnitItem(const std::string & name, const std::string & symbol,
	   const std::string & latex_symbol,
	   const std::string & desc) noexcept
    : name(name), symbol(symbol), description(desc), latex_symbol(latex_symbol)
  {
    // empty
  }

  /** Convert the item to a string representation.

      @return A string containing the name, symbol, and description.
  */
  std::string to_string() const
  {
    std::ostringstream s;
    s << "UnitItem name = " << name << std::endl
      << "Symbol        = " << symbol << std::endl
      << "Description   = " << description;
    return s.str();
  }

  /** Convert the item to a formatted string representation.

      @param[in] width The width for text alignment.
      @param[in] left_margin The number of spaces for the left margin.
      @return A formatted string.
  */
  std::string to_string(std::size_t width, std::size_t left_margin = 0) const
  {
    const std::string margin(left_margin, ' ');
    std::ostringstream s;
    s << margin << "UnitItem name = " << name << std::endl
      << margin << "Symbol        = " << symbol << std::endl
      << margin << "Description   = "
      << align_text_to_left_except_first(description, width, 16);
    return s.str();
  }

  /** Stream insertion operator.

      Allows printing the UnitItem to an output stream.
  */
  friend std::ostream & operator << (std::ostream & out, const UnitItem & ui)
  {
    return out << ui.to_string();
  }
};

/** Basic table storing physical quantities and unit descriptors.

    This class maintains two indices for `UnitItem` objects: one by name and one by symbol.
    It ensures uniqueness of names and symbols within the table.

    @author Leandro Rabindranath Leon
    @ingroup Units
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
  DynList<std::string> names() const { return name_tbl.keys(); }

  /// Return all the stored descriptor symbols.
  DynList<std::string> symbols() const { return symbol_tbl.keys(); }

  /// Return an iterator to a list of std::pair<std::string, const UnitItem*>
  /// items. First item is the descriptor name and the second one is a
  /// pointer to the descriptor.
  auto get_it() { return name_tbl.get_it(); }

  /** Register a new descriptor.

      @param[in] ptr pointer to the descriptor. It must correctly allocated.
      @throw bad_alloc if there is no enough memory.
      @throw std::domain_error if it already exists a descriptor with the
      same name or the same symbol.
   */
  void register_item(const UnitItem * ptr)
  {
    ah_domain_error_if(name_tbl.contains(ptr->name))
      << " name " << ptr->name << " already exist";

    ah_domain_error_if(symbol_tbl.contains(ptr->symbol))
      << "unit symbol " << ptr->symbol << " already exist";
    
    name_tbl.insert(ptr->name, ptr);
    symbol_tbl.insert(ptr->symbol, ptr);
  }

  /// Return true if the table contains a descriptor with name `name`.
  bool exists_name(const std::string & name) const noexcept
  {
    return name_tbl.contains(name);
  }

  /// Return true if the table contains a descriptor with symbol `symbol`.
  bool exists_symbol(const std::string & symbol) const noexcept
  {
    return symbol_tbl.contains(symbol);
  }

  /// Return a pointer to the descriptor containing the name `name` if
  /// this exists; otherwise, it returns `nullptr`
  const UnitItem * search_by_name(const std::string & name) const noexcept
  {
    auto p = name_tbl.search(name);
    return p ? p->second : nullptr;
  }

  /// Return a pointer to the descriptor containing the symbol `symbol` if
  /// this exists; otherwise, it returns `nullptr`
  const UnitItem * search_by_symbol(const std::string & symbol) const noexcept
  {
    auto p = symbol_tbl.search(symbol);
    return p ? p->second : nullptr;
  }

  /// Return the number of descriptors stored.
  std::size_t size() const noexcept { return name_tbl.size(); }

  /// Throw `std::domain_error` exception if the descriptor pointed by
  /// `ptr` already contains the std::string `str` as name or symbol. It is
  /// a helper validation function.
  void validate(const UnitItem * ptr, const std::string & str)
  {
    {
      const std::string & name = ptr->name;
      ah_domain_error_if(exists_name(str))
	<< "Repeated " << str << " name " << name;
    }

    {
      const std::string & symbol = ptr->symbol;
      ah_domain_error_if(exists_symbol(str))
	<< "Repeated " << str << " symbol " << symbol;
    }
  }
};


# endif // DESC_TABLE_H
