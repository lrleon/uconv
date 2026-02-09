physical_quantity :KinematicViscosity do
  symbol "nu"
  latex "\\nu"
  description "Ratio of dynamic viscosity to density"
end

unit :Meter2_S do
  symbol "m2/s"
  latex "m^{2}/s"
  description "SI unit of kinematic viscosity"
  quantity :KinematicViscosity
  range 0..1e4
end

unit :CentiStokes do
  symbol "cSt"
  latex "cSt"
  description "Centistokes, equal to 1e-6 m2/s"
  quantity :KinematicViscosity
  range 0..1e10
end

unit :Stokes do
  symbol "St"
  latex "St"
  description "Stokes, equal to 1e-4 m2/s"
  quantity :KinematicViscosity
  range 0..1e8
end

unit :Feet2_S do
  symbol "ft2/s"
  latex "ft^{2}/s"
  description "Square feet per second"
  quantity :KinematicViscosity
  range 0..107639.10416709722
end

# To Meter2_S
conversion :CentiStokes, :Meter2_S do |v| "1e-6 * #{v}" end
conversion :Stokes, :Meter2_S do |v| "1e-4 * #{v}" end
conversion :Feet2_S, :Meter2_S do |v| "9.290304e-2 * #{v}" end

# To CentiStokes
conversion :Meter2_S, :CentiStokes do |v| "1e6 * #{v}" end
conversion :Stokes, :CentiStokes do |v| "100 * #{v}" end
conversion :Feet2_S, :CentiStokes do |v| "92903.04 * #{v}" end

# To Stokes
conversion :Meter2_S, :Stokes do |v| "1e4 * #{v}" end
conversion :CentiStokes, :Stokes do |v| "1e-2 * #{v}" end
conversion :Feet2_S, :Stokes do |v| "929.0304 * #{v}" end

# To Feet2_S
conversion :Meter2_S, :Feet2_S do |v| "10.763910416709722 * #{v}" end
conversion :CentiStokes, :Feet2_S do |v| "1.0763910416709721e-5 * #{v}" end
conversion :Stokes, :Feet2_S do |v| "1.0763910416709721e-3 * #{v}" end
