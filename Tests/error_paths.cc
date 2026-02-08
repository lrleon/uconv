/*
   _   _  ___ ___  _ ____   __
  | | | |/ __/ _ \| '_ \ \ / /  C++ Physical magnitudes and units conversion
  | |_| | (_| (_) | | | \ V /   Version 1.0
   \__,_|\___\___/|_| |_|\_/    https://github.com/lrleon/uconv
*/
# include <gtest/gtest.h>

# include <uconv-list.H>

UnitsInstancer error_paths_init;

TEST(ErrorPaths, UnknownUnits)
{
  EXPECT_EQ(Unit::search_by_name("definitely_unknown_unit_name"), nullptr);
  EXPECT_EQ(Unit::search_by_symbol("definitely_unknown_unit_symbol"), nullptr);

  EXPECT_THROW(VtlQuantity("definitely_unknown_unit_name", 1.0), std::exception);
  EXPECT_THROW(unit_convert_name_to_name("meter", 1.0,
                                         "definitely_unknown_unit_name"),
               std::exception);
  EXPECT_THROW(unit_convert_symbol_to_symbol("m", 1.0,
                                             "definitely_unknown_unit_symbol"),
               std::exception);
}

TEST(ErrorPaths, MissingConversions)
{
  EXPECT_FALSE(exist_conversion("m", "sec"));
  EXPECT_FALSE(exist_conversion("meter", "second"));

  EXPECT_THROW(unit_convert_symbol_to_symbol("m", 1.0, "sec"), std::exception);
  EXPECT_THROW(unit_convert_name_to_name("meter", 1.0, "second"), std::exception);
}

TEST(ErrorPaths, OutOfRangeValues)
{
  EXPECT_THROW(VtlQuantity("m", 1e9), std::exception);
  EXPECT_THROW(VtlQuantity("degK", -1e3), std::exception);
}

TEST(ErrorPaths, InvalidEpsilonRatio)
{
  const Unit * const m = Unit::search_by_symbol("m");
  ASSERT_NE(m, nullptr);

  EXPECT_THROW(m->set_epsilon(0.0), std::exception);
  EXPECT_THROW(m->set_epsilon(0.31), std::exception);
}

TEST(ErrorPaths, IncompatibleQuantities)
{
  const VtlQuantity length("m", 2.0);
  const VtlQuantity time("sec", 1.0);

  EXPECT_THROW(static_cast<void>(length + time), std::exception);
  EXPECT_THROW(static_cast<void>(length - time), std::exception);
  EXPECT_THROW(static_cast<void>(length < time), std::exception);
}

TEST(ErrorPaths, MissingCompoundUnits)
{
  const VtlQuantity temperature("degC", 25.0);
  const VtlQuantity length("m", 2.0);

  EXPECT_THROW(static_cast<void>(temperature * length), std::exception);
  EXPECT_THROW(static_cast<void>(temperature / length), std::exception);
}

TEST(ErrorPaths, QuantityAndVtlExactUnitMismatch)
{
  const Quantity<meter> m = 1.0;
  const VtlQuantity ft("ft", 1.0);

  EXPECT_THROW(static_cast<void>(m + ft), std::exception);
  EXPECT_THROW(static_cast<void>(m - ft), std::exception);
}

TEST(ErrorPaths, NullQuantityDoubleAssignment)
{
  VtlQuantity q;
  ASSERT_TRUE(q.is_null());
  EXPECT_THROW(q = 42.0, std::exception);
}
