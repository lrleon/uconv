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

# include <uconv.H>

Declare_Physical_Quantity(CmpLengthPQ, "CmpL", "CmpL",
			  "Compound length quantity for testing");
Declare_Physical_Quantity(CmpTimePQ, "CmpT", "CmpT",
			  "Compound time quantity for testing");
Declare_Physical_Quantity(CmpVelocityPQ, "CmpV", "CmpV",
			  "Compound velocity quantity for testing");
Declare_Physical_Quantity(CmpAreaPQ, "CmpA", "CmpA",
			  "Compound area quantity for testing");

Declare_Unit(CmpLengthUnit, "cmp_lu", "cmp_lu", "compound length unit",
	     CmpLengthPQ, 0, 1e9);
Declare_Unit(CmpTimeUnit, "cmp_tu", "cmp_tu", "compound time unit",
	     CmpTimePQ, 1e-9, 1e9);
Declare_Product_Unit(CmpAreaUnit, "cmp_au", "compound area unit",
		     CmpAreaPQ, 0, 1e12, CmpLengthUnit, CmpTimeUnit);
Declare_Ratio_Unit(CmpVelocityUnit, "cmp_vu", "compound velocity unit",
		   CmpVelocityPQ, 0, 1e9, CmpLengthUnit, CmpTimeUnit);

TEST(Compound, RuntimeLookupProduct)
{
  const Unit & u1 = VtlQuantity::verify_product_compound(CmpLengthUnit::get_instance(),
							  CmpTimeUnit::get_instance());
  EXPECT_EQ(&u1, &CmpAreaUnit::get_instance());

  const Unit & u2 = VtlQuantity::verify_product_compound(CmpTimeUnit::get_instance(),
							  CmpLengthUnit::get_instance());
  EXPECT_EQ(&u2, &CmpAreaUnit::get_instance());
}

TEST(Compound, RuntimeLookupRatio)
{
  const Unit & u = VtlQuantity::verify_ratio_compound(CmpLengthUnit::get_instance(),
						      CmpTimeUnit::get_instance());
  EXPECT_EQ(&u, &CmpVelocityUnit::get_instance());

  EXPECT_THROW(VtlQuantity::verify_ratio_compound(CmpTimeUnit::get_instance(),
						  CmpLengthUnit::get_instance()),
	       std::exception);
}

TEST(Compound, QuantityOps)
{
  Quantity<CmpLengthUnit> length = 120;
  Quantity<CmpTimeUnit> time = 6;
  Quantity<CmpVelocityUnit> velocity = length / time;

  EXPECT_NEAR(velocity.raw(), 20, 1e-12);
}

TEST(Compound, VtlQuantityOps)
{
  VtlQuantity length(CmpLengthUnit::get_instance(), 120);
  VtlQuantity time(CmpTimeUnit::get_instance(), 6);

  const VtlQuantity velocity = length / time;
  const VtlQuantity area = length * time;

  EXPECT_EQ(&velocity.unit, &CmpVelocityUnit::get_instance());
  EXPECT_NEAR(velocity.raw(), 20, 1e-12);
  EXPECT_EQ(&area.unit, &CmpAreaUnit::get_instance());
  EXPECT_NEAR(area.raw(), 720, 1e-12);
}
