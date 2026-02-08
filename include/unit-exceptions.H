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
/** @file unit-exceptions.H
    @brief Defines exception classes for the uconv library.

    This file uses the Aleph-w exception macros to define specific exceptions
    that can be thrown during unit operations, such as invalid conversions,
    out-of-range values, or mismatched units.

    @author Leandro Rabindranath Leon
    @ingroup Units
*/

#ifndef UNIT_EXCEPTIONS_H
#define UNIT_EXCEPTIONS_H

# include <aleph-exceptions.H>

/** Thrown when a physical quantity is invalid or not recognized.
    @ingroup Units
*/
DEFINE_ALEPH_EXCEPTION(InvalidPhysicalQuantity, "Invalid physical quantity")

/** Thrown when attempting an operation between units that do not belong to the same physical quantity.
    @ingroup Units
*/
DEFINE_ALEPH_EXCEPTION(WrongSiblingUnit,
		     "Sibling unit is not physically related");

/** Thrown when an invalid ratio is provided for unit epsilon calculation.
    @ingroup Units
*/
DEFINE_ALEPH_EXCEPTION(WrongUnitRatio, "wrong unit ratio");

/** Thrown when a conversion between two units has not been registered.
    @ingroup Units
*/
DEFINE_ALEPH_EXCEPTION(UnitConversionNotFound, "Unit conversion not found");

/** Thrown when attempting to register a unit conversion that already exists.
    @ingroup Units
*/
DEFINE_ALEPH_EXCEPTION(DuplicatedUnitConversion, "duplicated unit conversion")

/** Thrown when a value exceeds the defined valid range for a unit.
    @ingroup Units
*/
DEFINE_ALEPH_EXCEPTION(OutOfUnitRange, "Value is out of unit range");

/** Thrown when a binary operation (like addition) is attempted on quantities with different units without implicit conversion.
    @ingroup Units
*/
DEFINE_ALEPH_EXCEPTION(DifferentUnits,
		     "Binary Operation between involves different units");

/** Thrown when a unit cannot be found by name or symbol.
    @ingroup Units
*/
DEFINE_ALEPH_EXCEPTION(UnitNotFound, "unit not found");

/** Thrown when a compound unit (product or ratio) cannot be found or derived.
    @ingroup Units
*/
DEFINE_ALEPH_EXCEPTION(CompoundUnitNotFound, "compound unit not found");

/** General base exception for unit-related errors.
    @ingroup Units
*/
DEFINE_ALEPH_EXCEPTION(UnitException, "unit exception");

#endif
