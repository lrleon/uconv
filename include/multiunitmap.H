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

# ifndef MULTIUNITMAP_H
# define MULTIUNITMAP_H

# include <tuple>
# include <initializer_list>
# include <ahSort.H>
# include <ahFunctional.H>
# include <tpl_dynMapTree.H>

using namespace std;

class Unit;

class CompoundUnitTbl
{
  struct Cmp
  {
    bool operator () (const DynList<string> & l1,
		      const DynList<string> & l2) const noexcept
    {
      return lesser(sort(l1), sort(l2));
    }
  };

  DynMapTree<DynList<string>, const Unit *, Avl_Tree, Cmp> tbl;

public:

  const Unit * search(const DynList<string> & names)
  {
    auto p = tbl.search(names);
    return p == nullptr ? nullptr : p->second;
  }

  bool insert(const DynList<string> & l, const Unit & unit)
  {
    return tbl.insert(l, &unit) != nullptr;
  }

  DynList<pair<DynList<string>, string>> items()
  {
    using T = pair<DynList<string>, string>;

    return tbl.items_ptr().maps<T>([] (pair<DynList<string>, const Unit*> * p)
      {
	return make_pair(p->first, p->second->name);
      });
  }
};


# endif // MULTIUNITMAP_H
