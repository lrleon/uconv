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

# include <ahFunctional.H>
# include <ah-string-utils.H>

# include <uconv-list.H>

UnitsInstancer init;

TEST(Basic, Temperature)
{
  EXPECT_EQ(Temperature::get_instance().name, "Temperature");
  EXPECT_EQ(Temperature::get_instance().symbol, "T");

  EXPECT_TRUE(eq(sort(Temperature::get_instance().units(), [] (auto p1, auto p2)
		      { return p1->name < p2->name; }),
		 build_dynlist<const Unit*>(&Celsius::get_instance(),
					    &Fahrenheit::get_instance(),
					    &Kelvin::get_instance(),
					    &Rankine::get_instance())));
}

TEST(Basic, Physical_static)
{
  EXPECT_FALSE(PhysicalQuantity::quantities().is_empty());

  EXPECT_EQ(PhysicalQuantity::search("Temperature"),
	    &Temperature::get_instance());
  EXPECT_NE(PhysicalQuantity::search("Angle"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Area"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Current"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Density"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Diameter"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Dimension_Less"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("FlowRate"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Frequency"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Length"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Power"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Pressure"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Time"), nullptr);
  EXPECT_NE(PhysicalQuantity::search("Velocity"), nullptr);
}
