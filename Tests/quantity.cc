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
# include <gmock/gmock.h>

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
  EXPECT_TRUE(eq(sort(PhysicalQuantity::quantities(), [] (auto p1, auto p2)
		      { return p1->name < p2->name; }),
		 build_dynlist<const PhysicalQuantity*>
		 (&Angle::get_instance(), &Area::get_instance(),
		  &Current::get_instance(), &Density::get_instance(),
		  &DummyUnit::get_instance(),
		  &Frequency::get_instance(), &Pressure::get_instance(),
		  &Temperature::get_instance(), &Time::get_instance())));

  EXPECT_EQ(PhysicalQuantity::search("Temperature"),
	    &Temperature::get_instance());

  EXPECT_TRUE(eq(PhysicalQuantity::names(),
		 build_dynlist<string>("Angle", "Area", "Current", "Density",
				       "DummyUnit", "Frequency",  "Pressure",
				       "Temperature", "Time")));
}
