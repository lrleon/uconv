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
/** @file multiunitmap.H
    @brief Defines the data structures for managing compound units.

    This file contains the definition of `CompoundUnitTbl` and related structures,
    which are used to store and retrieve units that are composed of other units
    (e.g., "meter/second" or "Newton*meter").

    @author Leandro Rabindranath Leon
    @ingroup Units
*/

# ifndef MULTIUNITMAP_H
# define MULTIUNITMAP_H

# include <string>
# include <tuple>
# include <initializer_list>
# include <ahSort.H>
# include <ahFunctional.H>
# include <tpl_dynMapTree.H>


class Unit;

/** Operation type for compound units.

    Distinguishes between units formed by multiplication (Product) and division (Ratio).
*/
enum class CompoundUnitOp
{
  Product = 0, ///< Units are multiplied (e.g., N*m)
  Ratio = 1    ///< Units are divided (e.g., m/s)
};

/** Table for storing and retrieving compound units.

    This class maps a combination of unit names and an operation (product or ratio)
    to a resulting `Unit` object. It allows the system to automatically identify
    the resulting unit of arithmetic operations between quantities.

    For example, if we multiply a quantity in "Newtons" by a quantity in "meters",
    this table can be used to find that the resulting unit is "Joules".

    The table handles commutativity for products (A*B is the same as B*A) by sorting
    the unit names before searching or inserting. For ratios, order matters (A/B != B/A).
*/
class CompoundUnitTbl
{
  /** Internal key structure for the map.

      Combines the operation type and the list of unit names involved.
  */
  struct Key
  {
    CompoundUnitOp op;
    DynList<std::string> names;

    Key() noexcept : op(CompoundUnitOp::Product), names() {}
    Key(CompoundUnitOp o, const DynList<std::string> & n) : op(o), names(n) {}
  };

  /** Comparator for Keys.

      Ensures consistent ordering for map lookups.
      - Products are treated as commutative: the list of names is sorted before comparison.
      - Ratios are non-commutative: the list of names is compared as-is.
  */
  struct Cmp
  {
    bool operator ()(const Key & k1, const Key & k2) const noexcept
    {
      if (k1.op != k2.op)
        return static_cast<int>(k1.op) < static_cast<int>(k2.op);

      if (k1.op == CompoundUnitOp::Product)
        return lesser(sort(k1.names), sort(k2.names));

      return lesser(k1.names, k2.names);
    }
  };

  /// The underlying map structure mapping Keys to Unit pointers.
  DynMapTree<Key, const Unit *, Avl_Tree, Cmp> tbl;

  const Unit * search(const Key & key)
  {
    auto p = tbl.search(key);
    return p == nullptr ? nullptr : p->second;
  }

  bool insert(const Key & key, const Unit & unit)
  {
    return tbl.insert(key, &unit) != nullptr;
  }

public:
  /** Search for a unit resulting from the product of the given unit names.

      @param[in] names List of unit names involved in the product.
      @return Pointer to the resulting Unit, or nullptr if not found.
  */
  const Unit * search_product(const DynList<std::string> & names)
  {
    return search({CompoundUnitOp::Product, names});
  }

  /** Search for a unit resulting from the ratio of the given unit names.

      @param[in] names List of unit names involved in the ratio (numerator, denominator(s)).
      @return Pointer to the resulting Unit, or nullptr if not found.
  */
  const Unit * search_ratio(const DynList<std::string> & names)
  {
    return search({CompoundUnitOp::Ratio, names});
  }

  /** Register a new compound unit formed by product.

      @param[in] names List of component unit names.
      @param[in] unit The resulting compound unit.
      @return true if insertion was successful, false if it already existed.
  */
  bool insert_product(const DynList<std::string> & names, const Unit & unit)
  {
    return insert({CompoundUnitOp::Product, names}, unit);
  }

  /** Register a new compound unit formed by ratio.

      @param[in] names List of component unit names.
      @param[in] unit The resulting compound unit.
      @return true if insertion was successful, false if it already existed.
  */
  bool insert_ratio(const DynList<std::string> & names, const Unit & unit)
  {
    return insert({CompoundUnitOp::Ratio, names}, unit);
  }

  /** Retrieve all registered compound units.

      @return A list of pairs, where each pair contains the list of component names and the name of the resulting unit.
  */
  DynList<std::pair<DynList<std::string>, std::string>> items()
  {
    using T = std::pair<DynList<std::string>, std::string>;

    return tbl.items_ptr().maps<T>([](std::pair<Key, const Unit *> *p)
                                     {
                                       return std::make_pair(p->first.names, p->second->name);
                                     });
  }
};


# endif // MULTIUNITMAP_H
