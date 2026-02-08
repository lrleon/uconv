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
# ifndef MULTIUNITMAP_H
# define MULTIUNITMAP_H

# include <tuple>
# include <initializer_list>
# include <ahSort.H>
# include <ahFunctional.H>
# include <tpl_dynMapTree.H>

using namespace std;

class Unit;

enum class CompoundUnitOp
{
  Product = 0,
  Ratio = 1
};

class CompoundUnitTbl
{
  struct Key
  {
    CompoundUnitOp op = CompoundUnitOp::Product;
    DynList<string> names;
  };

  struct Cmp
  {
    bool operator () (const Key & k1, const Key & k2) const noexcept
    {
      if (k1.op != k2.op)
	return static_cast<int>(k1.op) < static_cast<int>(k2.op);

      if (k1.op == CompoundUnitOp::Product)
	return lesser(sort(k1.names), sort(k2.names));

      return lesser(k1.names, k2.names);
    }
  };

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

  const Unit * search_product(const DynList<string> & names)
  {
    return search({CompoundUnitOp::Product, names});
  }

  const Unit * search_ratio(const DynList<string> & names)
  {
    return search({CompoundUnitOp::Ratio, names});
  }

  bool insert_product(const DynList<string> & names, const Unit & unit)
  {
    return insert({CompoundUnitOp::Product, names}, unit);
  }

  bool insert_ratio(const DynList<string> & names, const Unit & unit)
  {
    return insert({CompoundUnitOp::Ratio, names}, unit);
  }

  DynList<pair<DynList<string>, string>> items()
  {
    using T = pair<DynList<string>, string>;

    return tbl.items_ptr().maps<T>([] (pair<Key, const Unit*> * p)
      {
	return make_pair(p->first.names, p->second->name);
      });
  }
};


# endif // MULTIUNITMAP_H
