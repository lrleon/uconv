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
# include <gtest/gtest.h>

# include <unititem.H>

TEST(Table, basic)
{
  UnitItemTable tbl;

  EXPECT_EQ(tbl.size(), 0);
  EXPECT_TRUE(tbl.items().is_empty());
  EXPECT_TRUE(tbl.names().is_empty());
  EXPECT_TRUE(tbl.names().is_empty());
}

TEST(Table, operations)
{
  UnitItemTable tbl;
  UnitItem u1("Unit1", "u1", "first unit");
  UnitItem u2("Unit2", "u2", "second unit");
  UnitItem repeated_uname("Unit1", "x", "desc");
  UnitItem repeated_symbol("Unit", "u1", "desc");

  EXPECT_NO_THROW(tbl.register_item(&u1));
  EXPECT_NO_THROW(tbl.register_item(&u2));

  EXPECT_THROW(tbl.register_item(&u1), domain_error);
  EXPECT_THROW(tbl.register_item(&u2), domain_error);
  EXPECT_THROW(tbl.register_item(&repeated_uname), domain_error);
  EXPECT_THROW(tbl.register_item(&repeated_symbol), domain_error);

  EXPECT_TRUE(tbl.exists_name("Unit1"));
  EXPECT_TRUE(tbl.exists_name("Unit2"));
  EXPECT_FALSE(tbl.exists_name("Unit"));
  EXPECT_TRUE(tbl.exists_symbol("u1"));
  EXPECT_TRUE(tbl.exists_symbol("u2"));
  EXPECT_FALSE(tbl.exists_symbol("u"));

  EXPECT_EQ(tbl.search_by_name("Unit1"), &u1);
  EXPECT_EQ(tbl.search_by_name("Unit2"), &u2);
  EXPECT_EQ(tbl.search_by_name("Unit"), nullptr);
  EXPECT_EQ(tbl.search_by_symbol("u1"), &u1);
  EXPECT_EQ(tbl.search_by_symbol("u2"), &u2);
  EXPECT_EQ(tbl.search_by_symbol("u"), nullptr);

  EXPECT_EQ(tbl.size(), 2);

  EXPECT_THROW(tbl.validate(&u1, "Unit1"), domain_error);
  EXPECT_THROW(tbl.validate(&u1, "Unit2"), domain_error);
  EXPECT_THROW(tbl.validate(&u1, "u1"), domain_error);
  EXPECT_THROW(tbl.validate(&u1, "u2"), domain_error);

  EXPECT_TRUE(eq(tbl.items(), build_dynlist<const UnitItem*>(&u1, &u2)));
  EXPECT_TRUE(eq(tbl.names(), build_dynlist<string>("Unit1", "Unit2")));
  EXPECT_TRUE(eq(tbl.symbols(), build_dynlist<string>("u1", "u2")));
}


