/* 
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

# include <gmock/gmock.h>

# include <unititem.H>

TEST(Table, basic)
{
  UnitItemTable tbl;

  EXPECT_EQ(tbl.size(), 0);
  EXPECT_TRUE(tbl.items().is_empty());
  EXPECT_TRUE(tbl.names().is_empty());
  EXPECT_TRUE(tbl.names().is_empty());
}
