physical_quantity :DynamicViscosity do
  symbol "mu"
  latex "\\mu"
  description "Resistance of a fluid to shear or flow"
end

unit :PascalSecond do
  symbol "Pa*s"
  latex "Pa\\cdot s"
  description "SI unit of dynamic viscosity"
  quantity :DynamicViscosity
  range 0..1e6
end

unit :Centipoise do
  symbol "cP"
  latex "cP"
  description "Centipoise, equal to 1 mPa*s"
  quantity :DynamicViscosity
  range 0..1e9
end

unit :Poise do
  symbol "P"
  latex "P"
  description "Poise, CGS unit of dynamic viscosity"
  quantity :DynamicViscosity
  range 0..1e7
end

unit :Lb_Ft_S do
  symbol "lb/ft*s"
  latex "lb/(ft\\cdot s)"
  description "Pound mass per foot-second"
  quantity :DynamicViscosity
  range 0..671968.9751393054
end

# To PascalSecond
conversion :Centipoise, :PascalSecond do |v| "1e-3 * #{v}" end
conversion :Poise, :PascalSecond do |v| "0.1 * #{v}" end
conversion :Lb_Ft_S, :PascalSecond do |v| "1.48816394357 * #{v}" end

# To Centipoise
conversion :PascalSecond, :Centipoise do |v| "1000 * #{v}" end
conversion :Poise, :Centipoise do |v| "100 * #{v}" end
conversion :Lb_Ft_S, :Centipoise do |v| "1488.16394357 * #{v}" end

# To Poise
conversion :PascalSecond, :Poise do |v| "10 * #{v}" end
conversion :Centipoise, :Poise do |v| "1e-2 * #{v}" end
conversion :Lb_Ft_S, :Poise do |v| "14.8816394357 * #{v}" end

# To Lb_Ft_S
conversion :PascalSecond, :Lb_Ft_S do |v| "0.6719689751393054 * #{v}" end
conversion :Centipoise, :Lb_Ft_S do |v| "6.719689751393054e-4 * #{v}" end
conversion :Poise, :Lb_Ft_S do |v| "6.719689751393054e-2 * #{v}" end
