/*
   _   _  ___ ___  _ ____   __
  | | | |/ __/ _ \| '_ \ \ / /  C++ Physical magnitudes and units conversion
  | |_| | (_| (_) | | | \ V /   Version 1.0
   \__,_|\___\___/|_| |_|\_/    https://github.com/lrleon/uconv
*/
# include <gtest/gtest.h>

# include <cmath>
# include <string>
# include <type_traits>

# include <uconv-list.H>

UnitsInstancer api_ops_legacy_init;

Declare_Physical_Quantity(LegacyLengthPQ, "LegL", "LegL",
                          "Legacy length quantity for API compatibility tests");
Declare_Physical_Quantity(LegacyTimePQ, "LegT", "LegT",
                          "Legacy time quantity for API compatibility tests");
Declare_Physical_Quantity(LegacyAreaPQ, "LegA", "LegA",
                          "Legacy area quantity for API compatibility tests");
Declare_Physical_Quantity(LegacyVelocityPQ, "LegV", "LegV",
                          "Legacy velocity quantity for API compatibility tests");

Declare_Unit(LegacyLengthUnit, "leg_lu", "leg_lu", "legacy length unit",
             LegacyLengthPQ, 0, 1e6);
Declare_Unit(LegacyTimeUnit, "leg_tu", "leg_tu", "legacy time unit",
             LegacyTimePQ, 1e-6, 1e6);
Declare_Product_Unit(LegacyAreaUnit, "leg_au", "legacy area unit",
                     LegacyAreaPQ, 0, 1e12, LegacyLengthUnit, LegacyTimeUnit);
Declare_Ratio_Unit(LegacyVelocityUnit, "leg_vu", "legacy velocity unit",
                   LegacyVelocityPQ, 0, 1e12, LegacyLengthUnit, LegacyTimeUnit);

TEST(ApiOpsLegacy, LegacyCompoundLookupAlias)
{
  const auto * const product = search_product_compound_unit(
    LegacyLengthUnit::get_instance().name,
    LegacyTimeUnit::get_instance().name);
  ASSERT_NE(product, nullptr);

  const auto * const legacy = search_compound_unit(
    LegacyLengthUnit::get_instance().name,
    LegacyTimeUnit::get_instance().name);
  ASSERT_NE(legacy, nullptr);

  EXPECT_EQ(product, legacy);
  EXPECT_EQ(legacy, &LegacyAreaUnit::get_instance());
}

TEST(ApiOpsLegacy, LegacyVerifyCompoundAlias)
{
  const Unit & via_legacy = VtlQuantity::verify_compound(
    LegacyLengthUnit::get_instance(),
    LegacyTimeUnit::get_instance());

  const Unit & via_product = VtlQuantity::verify_product_compound(
    LegacyLengthUnit::get_instance(),
    LegacyTimeUnit::get_instance());

  EXPECT_EQ(&via_legacy, &via_product);
  EXPECT_EQ(&via_legacy, &LegacyAreaUnit::get_instance());
}

TEST(ApiOpsLegacy, CombineUnitsAlias)
{
  static_assert(std::is_same<typename Combine_Units<LegacyLengthUnit,
                                                    LegacyTimeUnit>::type,
                             LegacyVelocityUnit>::value,
                "Combine_Units alias must map to Divide_Units");

  const Quantity<LegacyLengthUnit> length = 24.0;
  const Quantity<LegacyTimeUnit> time = 6.0;
  Quantity<Combine_Units<LegacyLengthUnit, LegacyTimeUnit>::type> velocity =
    length / time;
  EXPECT_NEAR(velocity.raw(), 4.0, 1e-12);
}

TEST(ApiOpsLegacy, UnitFormattingAndBoundsHelpers)
{
  const Unit & m = meter::get_instance();

  const std::string formatted = m.to_string(48, 2);
  EXPECT_NE(formatted.find("  Unit name"), std::string::npos);
  EXPECT_NE(formatted.find("description"), std::string::npos);
  EXPECT_NE(formatted.find("physical quantity"), std::string::npos);

  const VtlQuantity min_q = m.min();
  const VtlQuantity max_q = m.max();
  EXPECT_EQ(&min_q.unit, &m);
  EXPECT_EQ(&max_q.unit, &m);
  EXPECT_DOUBLE_EQ(min_q.raw(), m.min_val);
  EXPECT_DOUBLE_EQ(max_q.raw(), m.max_val);

  EXPECT_DOUBLE_EQ(bind_to_unit_limits(m.min_val - 10.0, m), m.min_val);
  EXPECT_DOUBLE_EQ(bind_to_unit_limits(m.max_val + 10.0, m), m.max_val);
  EXPECT_DOUBLE_EQ(bind_to_unit_limits(12.5, m), 12.5);
}

TEST(ApiOpsLegacy, QuantityScalarOverloads)
{
  const Quantity<meter> q = 2.0;

  EXPECT_NEAR((1.5 + q).raw(), 3.5, 1e-12);
  EXPECT_NEAR((5.0 - q).raw(), 3.0, 1e-12);
  EXPECT_NEAR((2.0 * q).raw(), 4.0, 1e-12);
  EXPECT_NEAR((q * 3.0).raw(), 6.0, 1e-12);
  EXPECT_NEAR((10.0 / q).raw(), 5.0, 1e-12);
  EXPECT_NEAR((q / 2.0).raw(), 1.0, 1e-12);

  EXPECT_TRUE(q < 3.0);
  EXPECT_TRUE(3.0 > q);
  EXPECT_TRUE(q <= 2.0);
  EXPECT_TRUE(2.0 >= q);
  EXPECT_TRUE(q == 2.0);
  EXPECT_TRUE(2.0 == q);
  EXPECT_TRUE(q != 1.0);
  EXPECT_TRUE(1.0 != q);
}

TEST(ApiOpsLegacy, QuantityVtlAndMathHelpers)
{
  Quantity<meter> m = 2.0;
  const VtlQuantity one_m("m", 1.0);

  const VtlQuantity sum = m + one_m;
  const VtlQuantity diff = m - one_m;
  EXPECT_EQ(&sum.unit, &meter::get_instance());
  EXPECT_EQ(&diff.unit, &meter::get_instance());
  EXPECT_NEAR(sum.raw(), 3.0, 1e-12);
  EXPECT_NEAR(diff.raw(), 1.0, 1e-12);

  m += one_m;
  EXPECT_NEAR(m.raw(), 3.0, 1e-12);
  m -= one_m;
  EXPECT_NEAR(m.raw(), 2.0, 1e-12);

  const Quantity<meter> q = 2.0;
  EXPECT_NEAR(pow2(q), 4.0, 1e-12);
  EXPECT_NEAR(pow3(q), 8.0, 1e-12);
  EXPECT_NEAR(pow(q, 2.0), 4.0, 1e-12);
  EXPECT_NEAR(powl(q, 2.0L), 4.0, 1e-12);

  const Quantity<Dim_Less> one = 1.0;
  EXPECT_NEAR(exp(one), std::exp(1.0), 1e-12);
  EXPECT_NEAR(log(one), 0.0, 1e-12);
  EXPECT_NEAR(log10(one), 0.0, 1e-12);
  EXPECT_NEAR(sqrt(one), 1.0, 1e-12);
  EXPECT_NEAR(cbrt(one), 1.0, 1e-12);
}

TEST(ApiOpsLegacy, VtlScalarOverloadsAndNextPrev)
{
  VtlQuantity v("m", 2.0);

  EXPECT_NEAR((1.0 + v).raw(), 3.0, 1e-12);
  EXPECT_NEAR((v + 1.0).raw(), 3.0, 1e-12);
  EXPECT_NEAR((5.0 - v).raw(), 3.0, 1e-12);
  EXPECT_NEAR((v - 1.0).raw(), 1.0, 1e-12);
  EXPECT_NEAR((2.0 * v).raw(), 4.0, 1e-12);
  EXPECT_NEAR((v * 2.0).raw(), 4.0, 1e-12);
  EXPECT_NEAR((8.0 / v).raw(), 4.0, 1e-12);
  EXPECT_NEAR((v / 2.0).raw(), 1.0, 1e-12);

  EXPECT_TRUE(v < 3.0);
  EXPECT_TRUE(3.0 > v);
  EXPECT_TRUE(v <= 2.0);
  EXPECT_TRUE(2.0 >= v);
  EXPECT_TRUE(v == 2.0);
  EXPECT_TRUE(2.0 == v);
  EXPECT_TRUE(v != 1.0);
  EXPECT_TRUE(1.0 != v);

  const auto q_next = next_value(v);
  const auto q_prev = prev_value(v);
  EXPECT_EQ(&q_next.unit, &v.unit);
  EXPECT_EQ(&q_prev.unit, &v.unit);
  EXPECT_GT(q_next.raw(), v.raw());
  EXPECT_LT(q_prev.raw(), v.raw());

  const Quantity<meter> q = 2.0;
  EXPECT_GT(q.next().raw(), q.raw());
  EXPECT_LT(q.prev().raw(), q.raw());
}
