/*
   _   _  ___ ___  _ ____   __
  | | | |/ __/ _ \| '_ \ \ / /  C++ Physical magnitudes and units conversion
  | |_| | (_| (_) | | | \ V /   Version 1.0
   \__,_|\___\___/|_| |_|\_/    https://github.com/lrleon/uconv
*/
/** @file ah-uconv-errors.H
    @brief ah-errors-like helpers for uconv custom exceptions.

    This header mirrors the style of `ah-errors.H` for exception types that are
    specific to uconv and therefore not covered by the standard ah-errors macros.
*/

#ifndef AH_UCONV_ERRORS_H
#define AH_UCONV_ERRORS_H

#include <cstddef>
#include <sstream>
#include <utility>

#include "unit-exceptions.H"

namespace Uconv
{
  template <class E>
  struct AlephExceptionBuilder
  {
    std::size_t line_number = 0;
    const char *file_name = "";
    const char *type_name = "";

    AlephExceptionBuilder(std::size_t ln, const char *fn, const char *tn)
      : line_number(ln), file_name(fn), type_name(tn) {}

    [[noreturn]] void operator,(const std::ostream &s)
    {
      throw E(line_number, file_name, type_name,
              static_cast<const std::ostringstream &>(s).str());
    }
  };

  template <class E>
  struct StringCtorExceptionBuilder
  {
    [[noreturn]] void operator,(const std::ostream &s)
    {
      throw E(static_cast<const std::ostringstream &>(s).str());
    }
  };
}

#define ah_aleph_error_unless(type, C)                                     \
  if (not (C))                                                              \
    [[unlikely]] Uconv::AlephExceptionBuilder<type>(__LINE__, __FILE__, #type), \
      std::stringstream() << "(" << __FILE__ << ":" << __LINE__ << ") | "

#define ah_aleph_error_if(type, C)                                          \
  if (C)                                                                     \
    [[unlikely]] Uconv::AlephExceptionBuilder<type>(__LINE__, __FILE__, #type), \
      std::stringstream() << "(" << __FILE__ << ":" << __LINE__ << ") | "

#define ah_aleph_error(type)                                                \
  Uconv::AlephExceptionBuilder<type>(__LINE__, __FILE__, #type),           \
    std::stringstream() << "(" << __FILE__ << ":" << __LINE__ << ") | "

#define ah_string_ctor_error_unless(type, C)                                \
  if (not (C))                                                              \
    [[unlikely]] Uconv::StringCtorExceptionBuilder<type>(),                 \
      std::stringstream() << "(" << __FILE__ << ":" << __LINE__ << ") | "

#define ah_string_ctor_error_if(type, C)                                    \
  if (C)                                                                     \
    [[unlikely]] Uconv::StringCtorExceptionBuilder<type>(),                 \
      std::stringstream() << "(" << __FILE__ << ":" << __LINE__ << ") | "

#define ah_string_ctor_error(type)                                          \
  Uconv::StringCtorExceptionBuilder<type>(),                                \
    std::stringstream() << "(" << __FILE__ << ":" << __LINE__ << ") | "

// uconv-specific exceptions (not provided by ah-errors.H)
#define ah_invalid_physical_quantity_error_unless(C) ah_aleph_error_unless(InvalidPhysicalQuantity, C)
#define ah_invalid_physical_quantity_error_if(C) ah_aleph_error_if(InvalidPhysicalQuantity, C)
#define ah_invalid_physical_quantity_error() ah_aleph_error(InvalidPhysicalQuantity)

#define ah_wrong_sibling_unit_error_unless(C) ah_aleph_error_unless(WrongSiblingUnit, C)
#define ah_wrong_sibling_unit_error_if(C) ah_aleph_error_if(WrongSiblingUnit, C)
#define ah_wrong_sibling_unit_error() ah_aleph_error(WrongSiblingUnit)

#define ah_wrong_unit_ratio_error_unless(C) ah_aleph_error_unless(WrongUnitRatio, C)
#define ah_wrong_unit_ratio_error_if(C) ah_aleph_error_if(WrongUnitRatio, C)
#define ah_wrong_unit_ratio_error() ah_aleph_error(WrongUnitRatio)

#define ah_unit_conversion_not_found_error_unless(C) ah_aleph_error_unless(UnitConversionNotFound, C)
#define ah_unit_conversion_not_found_error_if(C) ah_aleph_error_if(UnitConversionNotFound, C)
#define ah_unit_conversion_not_found_error() ah_aleph_error(UnitConversionNotFound)

#define ah_duplicated_unit_conversion_error_unless(C) ah_aleph_error_unless(DuplicatedUnitConversion, C)
#define ah_duplicated_unit_conversion_error_if(C) ah_aleph_error_if(DuplicatedUnitConversion, C)
#define ah_duplicated_unit_conversion_error() ah_aleph_error(DuplicatedUnitConversion)

#define ah_out_of_unit_range_error_unless(C) ah_aleph_error_unless(OutOfUnitRange, C)
#define ah_out_of_unit_range_error_if(C) ah_aleph_error_if(OutOfUnitRange, C)
#define ah_out_of_unit_range_error() ah_aleph_error(OutOfUnitRange)

#define ah_different_units_error_unless(C) ah_aleph_error_unless(DifferentUnits, C)
#define ah_different_units_error_if(C) ah_aleph_error_if(DifferentUnits, C)
#define ah_different_units_error() ah_aleph_error(DifferentUnits)

#define ah_unit_not_found_error_unless(C) ah_aleph_error_unless(UnitNotFound, C)
#define ah_unit_not_found_error_if(C) ah_aleph_error_if(UnitNotFound, C)
#define ah_unit_not_found_error() ah_aleph_error(UnitNotFound)

#define ah_compound_unit_not_found_error_unless(C) ah_aleph_error_unless(CompoundUnitNotFound, C)
#define ah_compound_unit_not_found_error_if(C) ah_aleph_error_if(CompoundUnitNotFound, C)
#define ah_compound_unit_not_found_error() ah_aleph_error(CompoundUnitNotFound)

#define ah_unit_exception_error_unless(C) ah_aleph_error_unless(UnitException, C)
#define ah_unit_exception_error_if(C) ah_aleph_error_if(UnitException, C)
#define ah_unit_exception_error() ah_aleph_error(UnitException)

// Aleph custom exceptions used by uconv that are also not in ah-errors.H
#define ah_min_max_reversed_error_unless(C) ah_aleph_error_unless(MinMaxReversed, C)
#define ah_min_max_reversed_error_if(C) ah_aleph_error_if(MinMaxReversed, C)
#define ah_min_max_reversed_error() ah_aleph_error(MinMaxReversed)

#define ah_invalid_conversion_error_unless(C) ah_aleph_error_unless(InvalidConversion, C)
#define ah_invalid_conversion_error_if(C) ah_aleph_error_if(InvalidConversion, C)
#define ah_invalid_conversion_error() ah_aleph_error(InvalidConversion)

// Third-party exception type not covered by ah-errors.H
#define ah_tclap_arg_parse_error_unless(C) ah_string_ctor_error_unless(TCLAP::ArgParseException, C)
#define ah_tclap_arg_parse_error_if(C) ah_string_ctor_error_if(TCLAP::ArgParseException, C)
#define ah_tclap_arg_parse_error() ah_string_ctor_error(TCLAP::ArgParseException)

#endif
