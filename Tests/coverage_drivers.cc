/*
   _   _  ___ ___  _ ____   __
  | | | |/ __/ _ \| '_ \ \ / /  C++ Physical magnitudes and units conversion
  | |_| | (_| (_) | | | \ V /   Version 1.0
   \__,_|\___\___/|_| |_|\_/    https://github.com/lrleon/uconv
*/
# include <gtest/gtest.h>

# include <limits>
# include <sstream>
# include <string>

# include <uconv-list.H>

UnitsInstancer coverage_drivers_init;

Declare_Physical_Quantity(CovMissingPQ, "CovM", "CovM",
                          "Physical quantity used to drive missing conversion paths");
Declare_Unit(CovMissingA, "cov_a", "cov_a", "Coverage unit A",
             CovMissingPQ, 0, 1000);
Declare_Unit(CovMissingB, "cov_b", "cov_b", "Coverage unit B",
             CovMissingPQ, 0, 1000);
Declare_Conversion(CovMissingA, CovMissingB, V) { return 2.0 * V; }
UnitConverter<CovMissingA, CovMissingB> __uc__CovMissingA__to__CovMissingB;

namespace
{
  template <typename T>
  std::size_t dynlist_size(const DynList<T> & list)
  {
    std::size_t n = 0;
    for (auto it = list.get_it(); it.has_curr(); it.next())
      ++n;
    return n;
  }

  bool dynlist_contains(const DynList<std::string> & list, const std::string & value)
  {
    for (auto it = list.get_it(); it.has_curr(); it.next())
      if (it.get_curr() == value)
        return true;
    return false;
  }
}

TEST(CoverageDrivers, StringApisAndMetadata)
{
  const auto pq_names = PhysicalQuantity::names();
  EXPECT_TRUE(dynlist_contains(pq_names, "Length"));

  const Unit & m = meter::get_instance();
  EXPECT_GE(dynlist_size(m.family_units()), 1u);

  const std::string unit_dump = m.to_string();
  EXPECT_NE(unit_dump.find("Unit name"), std::string::npos);
  EXPECT_NE(unit_dump.find("symbol"), std::string::npos);

  std::ostringstream unit_stream;
  unit_stream << m;
  EXPECT_NE(unit_stream.str().find("Unit name"), std::string::npos);

  const VtlQuantity q("m", 12.5);
  const std::string quantity_dump = q.to_string();
  EXPECT_NE(quantity_dump.find("m"), std::string::npos);

  std::ostringstream quantity_stream;
  quantity_stream << q;
  EXPECT_NE(quantity_stream.str().find("m"), std::string::npos);
}

TEST(CoverageDrivers, ConversionErrorBranches)
{
  DynList<double> values;
  values.append(1.0);
  values.append(2.0);

  const auto same = unit_convert(meter::get_instance(), values, meter::get_instance());
  EXPECT_EQ(dynlist_size(same), dynlist_size(values));

  auto mutable_same = values;
  EXPECT_NO_THROW(mutable_unit_convert(meter::get_instance(), mutable_same,
                                       meter::get_instance()));
  EXPECT_EQ(dynlist_size(mutable_same), dynlist_size(values));

  EXPECT_THROW(unit_convert(meter::get_instance(), values, second::get_instance()),
               std::exception);
  auto mutable_missing = values;
  EXPECT_THROW(mutable_unit_convert(meter::get_instance(), mutable_missing,
                                    second::get_instance()),
               std::exception);
  EXPECT_THROW(unit_convert(meter::get_instance(), 1.0, second::get_instance()),
               std::exception);

  EXPECT_THROW(unit_convert_name_to_name("unknown_src_name", 1.0, "meter"),
               std::exception);
  EXPECT_THROW(unit_convert_name_to_name("meter", 1.0, "unknown_tgt_name"),
               std::exception);
  EXPECT_THROW(unit_convert_name_to_name("meter", 1.0, "second"),
               std::exception);

  EXPECT_THROW(unit_convert_symbol_to_symbol("unknown_src_symbol", 1.0, "m"),
               std::exception);
  EXPECT_THROW(unit_convert_symbol_to_symbol("m", 1.0, "unknown_tgt_symbol"),
               std::exception);
  EXPECT_THROW(unit_convert_symbol_to_symbol("m", 1.0, "sec"),
               std::exception);
}

TEST(CoverageDrivers, CheckConversionsNegativePath)
{
  const auto report = check_conversions(CovMissingPQ::get_instance());
  EXPECT_FALSE(report.first);
  EXPECT_FALSE(report.second.is_empty());

  bool found_missing_message = false;
  for (auto it = report.second.get_it(); it.has_curr(); it.next())
    {
      if (it.get_curr().find("Missing conversion from") != std::string::npos)
        {
          found_missing_message = true;
          break;
        }
    }
  EXPECT_TRUE(found_missing_message);
}

TEST(CoverageDrivers, VtlQuantityConstructorsAndAssignments)
{
  const Quantity<foot> qft = 3.0;

  const VtlQuantity same_symbol("ft", qft);
  const VtlQuantity diff_symbol("m", qft);
  const VtlQuantity same_unit(foot::get_instance(), qft);
  const VtlQuantity diff_unit(meter::get_instance(), qft);

  EXPECT_NEAR(same_symbol.raw(), 3.0, 1e-12);
  EXPECT_NEAR(same_unit.raw(), 3.0, 1e-12);
  EXPECT_NEAR(diff_symbol.raw(), 0.9144, 1e-9);
  EXPECT_NEAR(diff_unit.raw(), 0.9144, 1e-9);

  VtlQuantity self_assign("m", 1.0);
  const VtlQuantity & self_ref = self_assign;
  self_assign = self_ref;
  EXPECT_NEAR(self_assign.raw(), 1.0, 1e-12);

  VtlQuantity null_lhs;
  const VtlQuantity rhs("m", 2.0);
  null_lhs = rhs;
  EXPECT_FALSE(null_lhs.is_null());
  EXPECT_EQ(&null_lhs.unit, &meter::get_instance());
  EXPECT_NEAR(null_lhs.raw(), 2.0, 1e-12);

  VtlQuantity lhs("m", 3.0);
  const VtlQuantity null_rhs;
  EXPECT_THROW(lhs = null_rhs, std::exception);
  EXPECT_TRUE(lhs.is_null());

  VtlQuantity same_lhs("m", 1.0);
  const VtlQuantity same_rhs("m", 2.0);
  same_lhs = same_rhs;
  EXPECT_NEAR(same_lhs.raw(), 2.0, 1e-12);

  VtlQuantity diff_lhs("m", 1.0);
  const VtlQuantity diff_rhs("ft", 3.0);
  diff_lhs = diff_rhs;
  EXPECT_NEAR(diff_lhs.raw(), 0.9144, 1e-9);
}

TEST(CoverageDrivers, VtlQuantityDifferentUnitOps)
{
  const VtlQuantity one_m("m", 1.0);
  const VtlQuantity one_m_in_ft("ft", 3.280839895013123);
  const VtlQuantity two_m_in_ft("ft", 6.561679790026246);

  EXPECT_NEAR((one_m + one_m_in_ft).raw(), 2.0, 1e-9);
  EXPECT_NEAR((one_m - one_m_in_ft).raw(), 0.0, 1e-9);

  VtlQuantity acc("m", 1.0);
  acc += one_m_in_ft;
  EXPECT_NEAR(acc.raw(), 2.0, 1e-9);
  acc -= one_m_in_ft;
  EXPECT_NEAR(acc.raw(), 1.0, 1e-9);

  EXPECT_TRUE(one_m < two_m_in_ft);
  EXPECT_FALSE(two_m_in_ft < one_m);
}

TEST(CoverageDrivers, LookupNormalizationAndAliasPaths)
{
  const Unit * spaced = Unit::search_by_symbol(" \t m \n");
  ASSERT_NE(spaced, nullptr);
  EXPECT_EQ(spaced->symbol, "m");

  const Unit * omega = Unit::search_by_symbol("\xCE\xA9"); // Omega symbol
  ASSERT_NE(omega, nullptr);
  EXPECT_EQ(omega->symbol, "ohm");

  EXPECT_EQ(Unit::search_by_symbol("   \t   "), nullptr);

  EXPECT_FALSE(exist_conversion("m", "unknown_target_symbol"));
  EXPECT_EQ(search_conversion_fct("unknown_source_symbol", "m"), nullptr);
  EXPECT_EQ(search_conversion_fct("m", "unknown_target_symbol"), nullptr);
}

TEST(CoverageDrivers, BaseQuantityValidationEdgeCases)
{
  const Unit & m = meter::get_instance();
  const double just_over_max = m.max_val + 0.5 * m.get_epsilon();
  EXPECT_TRUE(BaseQuantity::is_valid(just_over_max, m));

  const double nan_value = std::numeric_limits<double>::quiet_NaN();
  EXPECT_TRUE(BaseQuantity::is_valid(nan_value, Unit::null_unit));

  VtlQuantity null_q;
  EXPECT_THROW(null_q = 1.0, std::exception);
}

TEST(CoverageDrivers, VtlQuantitySameUnitComparisonPath)
{
  const VtlQuantity one_m("m", 1.0);
  const VtlQuantity two_m("m", 2.0);

  EXPECT_TRUE(one_m < two_m);
  EXPECT_FALSE(two_m < one_m);
}
