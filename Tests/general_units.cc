/*
   _   _  ___ ___  _ ____   __
  | | | |/ __/ _ \| '_ \ \ / /  C++ Physical magnitudes and units conversion
  | |_| | (_| (_) | | | \ V /   Version 1.0
   \__,_|\___\___/|_| |_|\_/    https://github.com/lrleon/uconv
*/
# include <gtest/gtest.h>

# include <array>

# include <uconv-list.H>

UnitsInstancer general_units_init;

namespace
{
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
}

TEST(GeneralUnits, PhysicalQuantitiesRegistered)
{
  for (const char * const quantity_name : all_physical_quantities)
    {
      SCOPED_TRACE(quantity_name);
      EXPECT_NE(PhysicalQuantity::search(quantity_name), nullptr);
    }
}

TEST(GeneralUnits, MassConversions)
{
  const Quantity<Kilogram> one_kg = 1.0;
  const Quantity<PoundMass> in_lbm = one_kg;
  EXPECT_NEAR(in_lbm.raw(), 2.2046226218487757, 1e-12);

  const Quantity<Gram> in_g = one_kg;
  EXPECT_NEAR(in_g.raw(), 1000.0, 1e-12);

  const Quantity<Kilogram> back_to_kg = in_lbm;
  EXPECT_NEAR(back_to_kg.raw(), one_kg.raw(), 1e-12);
}

TEST(GeneralUnits, VolumeConversions)
{
  const Quantity<CubicMeter> one_m3 = 1.0;
  const Quantity<USGallon> in_gal = one_m3;
  EXPECT_NEAR(in_gal.raw(), 264.1720523581484, 1e-9);

  const Quantity<Barrel> in_bbl = one_m3;
  EXPECT_NEAR(in_bbl.raw(), 6.289810770432105, 1e-12);

  const Quantity<CubicMeter> back_to_m3 = in_gal;
  EXPECT_NEAR(back_to_m3.raw(), one_m3.raw(), 1e-9);
}

TEST(GeneralUnits, ForceConversions)
{
  const Quantity<Newton> one_n = 1.0;
  const Quantity<PoundForce> in_lbf = one_n;
  EXPECT_NEAR(in_lbf.raw(), 0.22480894387096263, 1e-12);

  const Quantity<Dyne> in_dyn = one_n;
  EXPECT_NEAR(in_dyn.raw(), 1e5, 1e-3);

  const Quantity<Newton> back_to_n = in_lbf;
  EXPECT_NEAR(back_to_n.raw(), one_n.raw(), 1e-8);
}

TEST(GeneralUnits, AccelerationConversions)
{
  const Quantity<Meter_S2> one_m_s2 = 1.0;
  const Quantity<Ft_S2> in_ft_s2 = one_m_s2;
  EXPECT_NEAR(in_ft_s2.raw(), 3.280839895013123, 1e-12);

  const Quantity<StandardGravity> in_g0 = one_m_s2;
  EXPECT_NEAR(in_g0.raw(), 0.10197162129779283, 1e-12);

  const Quantity<Meter_S2> back_to_m_s2 = in_ft_s2;
  EXPECT_NEAR(back_to_m_s2.raw(), one_m_s2.raw(), 1e-12);
}

TEST(GeneralUnits, EnergyConversions)
{
  const Quantity<Joule> energy_j = 3600.0;
  const Quantity<WattHour> energy_wh = energy_j;
  EXPECT_NEAR(energy_wh.raw(), 1.0, 1e-12);

  const Quantity<Joule> btu_j = 1055.05585262;
  const Quantity<BTU> energy_btu = btu_j;
  EXPECT_NEAR(energy_btu.raw(), 1.0, 1e-9);

  const Quantity<Joule> back_to_j = energy_wh;
  EXPECT_NEAR(back_to_j.raw(), energy_j.raw(), 1e-9);
}

TEST(GeneralUnits, TorqueConversions)
{
  const Quantity<NewtonMeter> one_nm = 1.0;
  const Quantity<PoundFoot> in_lbf_ft = one_nm;
  EXPECT_NEAR(in_lbf_ft.raw(), 0.7375621492772656, 1e-12);

  const Quantity<PoundInch> in_lbf_in = one_nm;
  EXPECT_NEAR(in_lbf_in.raw(), 8.850745791327183, 1e-12);

  const Quantity<NewtonMeter> back_to_nm = in_lbf_ft;
  EXPECT_NEAR(back_to_nm.raw(), one_nm.raw(), 1e-8);
}

TEST(GeneralUnits, MassFlowConversions)
{
  const Quantity<Kg_S> one_kg_s = 1.0;
  const Quantity<Kg_H> in_kg_h = one_kg_s;
  EXPECT_NEAR(in_kg_h.raw(), 3600.0, 1e-9);

  const Quantity<Lb_H> in_lb_h = one_kg_s;
  EXPECT_NEAR(in_lb_h.raw(), 7936.641438655593, 1e-6);

  const Quantity<Kg_S> back_to_kg_s = in_lb_h;
  EXPECT_NEAR(back_to_kg_s.raw(), one_kg_s.raw(), 1e-9);
}

TEST(GeneralUnits, DynamicViscosityConversions)
{
  const Quantity<PascalSecond> one_pa_s = 1.0;
  const Quantity<Centipoise> in_cp = one_pa_s;
  EXPECT_NEAR(in_cp.raw(), 1000.0, 1e-9);

  const Quantity<Poise> in_p = one_pa_s;
  EXPECT_NEAR(in_p.raw(), 10.0, 1e-12);

  const Quantity<PascalSecond> back_to_pa_s = in_cp;
  EXPECT_NEAR(back_to_pa_s.raw(), one_pa_s.raw(), 1e-9);
}

TEST(GeneralUnits, KinematicViscosityConversions)
{
  const Quantity<Meter2_S> one_m2_s = 1.0;
  const Quantity<CentiStokes> in_cst = one_m2_s;
  EXPECT_NEAR(in_cst.raw(), 1e6, 1e-3);

  const Quantity<Feet2_S> in_ft2_s = one_m2_s;
  EXPECT_NEAR(in_ft2_s.raw(), 10.763910416709722, 1e-12);

  const Quantity<Meter2_S> back_to_m2_s = in_ft2_s;
  EXPECT_NEAR(back_to_m2_s.raw(), one_m2_s.raw(), 1e-9);
}

TEST(GeneralUnits, VoltageConversions)
{
  const Quantity<Volt> one_v = 1.0;
  const Quantity<MilliVolt> in_mv = one_v;
  EXPECT_NEAR(in_mv.raw(), 1000.0, 1e-9);

  const Quantity<KiloVolt> in_kv = one_v;
  EXPECT_NEAR(in_kv.raw(), 1e-3, 1e-12);

  const Quantity<Volt> back_to_v = in_kv;
  EXPECT_NEAR(back_to_v.raw(), one_v.raw(), 1e-12);
}

TEST(GeneralUnits, ResistanceConversions)
{
  const Quantity<KiloOhm> one_kohm = 1.0;
  const Quantity<Ohm> in_ohm = one_kohm;
  EXPECT_NEAR(in_ohm.raw(), 1000.0, 1e-9);

  const Quantity<MegaOhm> in_mohm = one_kohm;
  EXPECT_NEAR(in_mohm.raw(), 1e-3, 1e-12);

  const Quantity<KiloOhm> back_to_kohm = in_mohm;
  EXPECT_NEAR(back_to_kohm.raw(), one_kohm.raw(), 1e-12);
}

TEST(GeneralUnits, CapacitanceConversions)
{
  const Quantity<Farad> one_f = 1.0;
  const Quantity<MicroFarad> in_uf = one_f;
  EXPECT_NEAR(in_uf.raw(), 1e6, 1e-3);

  const Quantity<PicoFarad> in_pf = one_f;
  EXPECT_NEAR(in_pf.raw(), 1e12, 1.0);

  const Quantity<Farad> back_to_f = in_uf;
  EXPECT_NEAR(back_to_f.raw(), one_f.raw(), 1e-9);
}

TEST(GeneralUnits, ChargeConversions)
{
  const Quantity<AmpereHour> one_ah = 1.0;
  const Quantity<Coulomb> in_c = one_ah;
  EXPECT_NEAR(in_c.raw(), 3600.0, 1e-9);

  const Quantity<MilliAmpereHour> in_mah = one_ah;
  EXPECT_NEAR(in_mah.raw(), 1000.0, 1e-9);

  const Quantity<AmpereHour> back_to_ah = in_c;
  EXPECT_NEAR(back_to_ah.raw(), one_ah.raw(), 1e-12);
}

TEST(GeneralUnits, SymbolAliasesAndNormalization)
{
  struct AliasCase
  {
    const char * alias;
    const char * normalized;
  };

  static const std::array<AliasCase, 26> alias_cases =
    {{
      {" s ", "sec"},
      {"SECOND", "sec"},
      {"seconds", "sec"},
      {" hr ", "h"},
      {"HOURS", "h"},
      {"day", "day"},
      {"days", "day"},
      {"\xCE\xA9", "ohm"}, // Ω
      {"\xE2\x84\xA6", "ohm"}, // Ω
      {"k\xCE\xA9", "kohm"}, // kΩ
      {"k\xE2\x84\xA6", "kohm"}, // kΩ
      {"M\xCE\xA9", "Mohm"}, // MΩ
      {"M\xE2\x84\xA6", "Mohm"}, // MΩ
      {"m\xCE\xA9", "mohm"}, // mΩ
      {"m\xE2\x84\xA6", "mohm"}, // mΩ
      {"\xCE\xBC" "F", "uF"}, // μF
      {"\xC2\xB5" "F", "uF"}, // µF
      {"\xCE\xBC" "f", "uF"}, // μf
      {"\xC2\xB5" "f", "uF"}, // µf
      {"\xC2\xB0" "C", "degC"}, // °C
      {"\xC2\xB0" "F", "degF"}, // °F
      {"\xC2\xB0" "R", "degR"}, // °R
      {"K", "degK"},
      {" sec ", "sec"},
      {" kohm ", "kohm"},
      {" degC ", "degC"}
    }};

  for (const auto & tc : alias_cases)
    {
      SCOPED_TRACE(tc.alias);
      const Unit * const unit = Unit::search_by_symbol(tc.alias);
      ASSERT_NE(unit, nullptr);
      EXPECT_EQ(unit->symbol, tc.normalized);
    }

  const VtlQuantity c_uF("\xC2\xB5" "F", 1.0); // µF
  const VtlQuantity c_nf("nF", c_uF);
  EXPECT_NEAR(c_nf.raw(), 1000.0, 1e-6);

  const VtlQuantity r_ohm("\xCE\xA9", 1000.0); // Ω
  const VtlQuantity r_kohm("kohm", r_ohm);
  EXPECT_NEAR(r_kohm.raw(), 1.0, 1e-9);

  const VtlQuantity dv(" lb / ft * s ", 1.0);
  EXPECT_EQ(dv.unit.symbol, "lb/ft*s");
}

TEST(GeneralUnits, FullCoverageCheck)
{
  for (const char * const quantity_name : all_physical_quantities)
    {
      SCOPED_TRACE(quantity_name);
      const auto * const quantity = PhysicalQuantity::search(quantity_name);
      ASSERT_NE(quantity, nullptr);
      const auto coverage = check_conversions(*quantity);
      EXPECT_TRUE(coverage.first);
    }
}
