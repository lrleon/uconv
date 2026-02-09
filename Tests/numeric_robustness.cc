/*
   _   _  ___ ___  _ ____   __
  | | | |/ __/ _ \| '_ \ \ / /  C++ Physical magnitudes and units conversion
  | |_| | (_| (_) | | | \ V /   Version 1.0
   \__,_|\___\___/|_| |_|\_/    https://github.com/lrleon/uconv
*/
# include <gtest/gtest.h>

# include <array>
# include <cstdint>
# include <cmath>
# include <random>
# include <string>
# include <algorithm>

# include <uconv-list.H>

UnitsInstancer numeric_robustness_init;

namespace
{
  constexpr double kRelativeRoundTripTolerance = 2e-5;

  constexpr std::array<const char *, 27> all_physical_quantities =
    {
      "Length",
      "Temperature",
      "Pressure",
      "Mass",
      "Volume",
      "Density",
      "MassFlow",
      "DynamicViscosity",
      "KinematicViscosity",
      "Acceleration",
      "Frequency",
      "Current",
      "Voltage",
      "Resistance",
      "Capacitance",
      "Charge",
      "Angle",
      "Time",
      "Area",
      "Power",
      "Energy",
      "Force",
      "Torque",
      "Diameter",
      "FlowRate",
      "Velocity",
      "Dimension_Less"
    };

  double relative_error(const double lhs, const double rhs)
  {
    const double scale = std::max(1.0, std::max(std::abs(lhs), std::abs(rhs)));
    return std::abs(lhs - rhs) / scale;
  }

  double sample_interior_value(const Unit & unit, std::mt19937_64 & rng)
  {
    const double span = unit.max_val - unit.min_val;
    double lo = unit.min_val;
    double hi = unit.max_val;

    if (span > 0)
      {
        lo = unit.min_val + 0.1 * span;
        hi = unit.max_val - 0.1 * span;
        if (not (lo < hi))
          {
            lo = unit.min_val;
            hi = unit.max_val;
          }
      }

    std::uniform_real_distribution<double> dist(lo, hi);
    return dist(rng);
  }
}

TEST(NumericRobustness, RandomRoundTripWithinPhysicalFamilies)
{
  for (const char * const quantity_name : all_physical_quantities)
    {
      SCOPED_TRACE(quantity_name);
      const auto * const quantity = PhysicalQuantity::search(quantity_name);
      ASSERT_NE(quantity, nullptr);

      const auto & units = quantity->units();
      ASSERT_FALSE(units.is_empty());
      std::size_t unit_count = 0;
      for (auto it = units.get_it(); it.has_curr(); it.next())
        ++unit_count;
      if (unit_count <= 1)
        continue;

      std::size_t pairs_with_samples = 0;

      for (auto it_src = units.get_it(); it_src.has_curr(); it_src.next())
        {
          const Unit * const src = it_src.get_curr();

          for (auto it_tgt = units.get_it(); it_tgt.has_curr(); it_tgt.next())
            {
              const Unit * const tgt = it_tgt.get_curr();
              if (src == tgt)
                continue;

              SCOPED_TRACE(src->name + std::string("->") + tgt->name);
              ASSERT_TRUE(exist_conversion(*src, *tgt));

              const auto seed =
                static_cast<std::uint64_t>(std::hash<std::string>{}(src->name + "->" + tgt->name));
              std::mt19937_64 rng(seed);

              std::size_t checked = 0;
              for (std::size_t i = 0; i < 80; ++i)
                {
                  const double source_value = sample_interior_value(*src, rng);
                  const double target_value = unit_convert(*src, source_value, *tgt);

                  if (not BaseQuantity::is_valid(target_value, *tgt))
                    continue;

                  const double roundtrip = unit_convert(*tgt, target_value, *src);
                  EXPECT_LE(relative_error(roundtrip, source_value), kRelativeRoundTripTolerance);
                  ++checked;
                }

              if (checked > 0)
                ++pairs_with_samples;
            }
        }

      EXPECT_GT(pairs_with_samples, 0u);
    }
}

TEST(NumericRobustness, BoundaryRoundTripWithinPhysicalFamilies)
{
  for (const char * const quantity_name : all_physical_quantities)
    {
      SCOPED_TRACE(quantity_name);
      const auto * const quantity = PhysicalQuantity::search(quantity_name);
      ASSERT_NE(quantity, nullptr);

      const auto & units = quantity->units();
      ASSERT_FALSE(units.is_empty());
      std::size_t unit_count = 0;
      for (auto it = units.get_it(); it.has_curr(); it.next())
        ++unit_count;
      if (unit_count <= 1)
        continue;

      std::size_t pairs_with_samples = 0;

      for (auto it_src = units.get_it(); it_src.has_curr(); it_src.next())
        {
          const Unit * const src = it_src.get_curr();
          const std::array<double, 3> values = {src->min_val, src->default_value(), src->max_val};

          for (auto it_tgt = units.get_it(); it_tgt.has_curr(); it_tgt.next())
            {
              const Unit * const tgt = it_tgt.get_curr();
              if (src == tgt)
                continue;

              SCOPED_TRACE(src->name + std::string("->") + tgt->name);
              std::size_t checked = 0;
              for (double source_value : values)
                {
                  const double target_value = unit_convert(*src, source_value, *tgt);
                  if (not BaseQuantity::is_valid(target_value, *tgt))
                    continue;

                  const double roundtrip = unit_convert(*tgt, target_value, *src);
                  EXPECT_LE(relative_error(roundtrip, source_value), kRelativeRoundTripTolerance);
                  ++checked;
                }

              if (checked > 0)
                ++pairs_with_samples;
            }
        }

      EXPECT_GT(pairs_with_samples, 0u);
    }
}

TEST(NumericRobustness, UnitRangeEdgesAndEpsilonWindow)
{
  const auto units = Unit::units();
  ASSERT_FALSE(units.is_empty());

  for (auto it = units.get_it(); it.has_curr(); it.next())
    {
      const Unit * const unit = it.get_curr();
      SCOPED_TRACE(unit->name);

      EXPECT_NO_THROW(VtlQuantity(*unit, unit->min_val));
      EXPECT_NO_THROW(VtlQuantity(*unit, unit->max_val));

      const double epsilon = unit->get_epsilon();
      if (not (epsilon > 0))
        continue;

      const double below_soft = unit->min_val - 0.5 * epsilon;
      if (below_soft > Unit_Invalid_Value)
        EXPECT_NO_THROW(VtlQuantity(*unit, below_soft));

      const double above_soft = unit->max_val + 0.5 * epsilon;
      EXPECT_NO_THROW(VtlQuantity(*unit, above_soft));

      const double below_hard = unit->min_val - 1.5 * epsilon;
      EXPECT_THROW(VtlQuantity(*unit, below_hard), std::exception);

      const double above_hard = unit->max_val + 1.5 * epsilon;
      EXPECT_THROW(VtlQuantity(*unit, above_hard), std::exception);
    }
}
