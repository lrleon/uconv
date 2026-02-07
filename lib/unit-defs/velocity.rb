physical_quantity :Velocity do
  symbol "V"
  latex "V"
  description "Rate of change of position"
end

unit :Ft_S do
  symbol "ft/s"
  latex "ft/s"
  description "feet for second"
  quantity :Velocity
  range 0..1e6
end

unit :Meter_S do
  symbol "m/s"
  latex "m/s"
  description "meter for second"
  quantity :Velocity
  range 0..304800
end

# To Ft_S
conversion :Meter_S, :Ft_S do |v| "3.28083989501312 * #{v}" end

# To Meter_S
conversion :Ft_S, :Meter_S do |v| "0.3048 * #{v}" end
