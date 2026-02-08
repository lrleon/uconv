/*
   _   _  ___ ___  _ ____   __
  | | | |/ __/ _ \| '_ \ \ / /  C++ Physical magnitudes and units conversion
  | |_| | (_| (_) | | | \ V /   Version 1.0
   \__,_|\___\___/|_| |_|\_/    https://github.com/lrleon/uconv
*/
# include <gtest/gtest.h>

# include <algorithm>

# include <nlohmann/json.hpp>

# include <uconv-list.H>

UnitsInstancer uconv_api_init;

TEST(UconvApi, CApiConversionHelpers)
{
  EXPECT_TRUE(conversion_exist("m", "ft"));
  EXPECT_FALSE(conversion_exist("m", "sec"));

  EXPECT_NEAR(unit_convert("m", "ft", 1.0), 3.28083989501, 1e-12);
  EXPECT_THROW(unit_convert("m", "sec", 1.0), std::exception);
}

TEST(UconvApi, SearchConversionFunction)
{
  const auto f_m_to_ft = search_conversion_fct("m", "ft");
  ASSERT_NE(f_m_to_ft, nullptr);
  EXPECT_NEAR((*f_m_to_ft)(2.0), 6.56167979002, 1e-11);

  EXPECT_EQ(search_conversion_fct("m", "sec"), nullptr);
}

TEST(UconvApi, JsonExportContainsCoreFields)
{
  const auto parsed = nlohmann::json::parse(units_json());
  ASSERT_TRUE(parsed.contains("uconv_physical_quantities"));
  ASSERT_TRUE(parsed["uconv_physical_quantities"].is_array());

  const auto & quantities = parsed["uconv_physical_quantities"];
  ASSERT_FALSE(quantities.empty());

  const auto it = std::find_if(quantities.begin(), quantities.end(),
			       [] (const auto & pq)
			       {
				 return pq.contains("name")
				   and pq["name"] == "Length";
			       });
  ASSERT_NE(it, quantities.end());
  ASSERT_TRUE(it->contains("units"));
  ASSERT_TRUE((*it)["units"].is_array());
  ASSERT_FALSE((*it)["units"].empty());
}

TEST(UconvApi, ContainerAndMutableConversions)
{
  DynList<double> fahrenheit;
  fahrenheit.append(32.0);
  fahrenheit.append(212.0);
  fahrenheit.append(-40.0);

  const auto celsius = unit_convert(Fahrenheit::get_instance(), fahrenheit,
				    Celsius::get_instance());

  auto it_c = celsius.get_it();
  ASSERT_TRUE(it_c.has_curr());
  EXPECT_NEAR(it_c.get_curr(), 0.0, 1e-12);
  it_c.next();
  ASSERT_TRUE(it_c.has_curr());
  EXPECT_NEAR(it_c.get_curr(), 100.0, 1e-12);
  it_c.next();
  ASSERT_TRUE(it_c.has_curr());
  EXPECT_NEAR(it_c.get_curr(), -40.0, 1e-12);
  it_c.next();
  EXPECT_FALSE(it_c.has_curr());

  auto mutable_vals = celsius;
  mutable_unit_convert(Celsius::get_instance(), mutable_vals,
		       Fahrenheit::get_instance());

  auto it_f = fahrenheit.get_it();
  auto it_back = mutable_vals.get_it();
  while (it_f.has_curr() and it_back.has_curr())
    {
      EXPECT_NEAR(it_back.get_curr(), it_f.get_curr(), 1e-12);
      it_f.next();
      it_back.next();
    }
  EXPECT_EQ(it_f.has_curr(), it_back.has_curr());
}

TEST(UconvApi, NextPrevValueHelpers)
{
  const VtlQuantity q("m", 1.0);
  const auto q_next = next_value(q);
  const auto q_prev = prev_value(q);

  EXPECT_EQ(&q_next.unit, &q.unit);
  EXPECT_EQ(&q_prev.unit, &q.unit);
  EXPECT_GT(q_next.raw(), q.raw());
  EXPECT_LT(q_prev.raw(), q.raw());
}
