physical_quantity :Acceleration do
  symbol "a"
  latex "a"
  description "Rate of change of velocity with respect to time"
end

unit :Meter_S2 do
  symbol "m/s2"
  latex "m/s^{2}"
  description "Acceleration in meters per second squared"
  quantity :Acceleration
  range -1e6..1e6
end

unit :Ft_S2 do
  symbol "ft/s2"
  latex "ft/s^{2}"
  description "Acceleration in feet per second squared"
  quantity :Acceleration
  range -3.280839895013123e6..3.280839895013123e6
end

unit :StandardGravity do
  symbol "g0"
  latex "g_{0}"
  description "Standard gravity acceleration"
  quantity :Acceleration
  range -1.0197162129779283e5..1.0197162129779283e5
end

unit :Gal do
  symbol "Gal"
  latex "Gal"
  description "Galileo (CGS acceleration unit), 1 Gal = 0.01 m/s2"
  quantity :Acceleration
  range -1e8..1e8
end

# To Meter_S2
conversion :Ft_S2, :Meter_S2 do |v| "0.3048 * #{v}" end
conversion :StandardGravity, :Meter_S2 do |v| "9.80665 * #{v}" end
conversion :Gal, :Meter_S2 do |v| "1e-2 * #{v}" end

# To Ft_S2
conversion :Meter_S2, :Ft_S2 do |v| "3.280839895013123 * #{v}" end
conversion :StandardGravity, :Ft_S2 do |v| "32.17404855643044 * #{v}" end
conversion :Gal, :Ft_S2 do |v| "3.280839895013123e-2 * #{v}" end

# To StandardGravity
conversion :Meter_S2, :StandardGravity do |v| "0.10197162129779283 * #{v}" end
conversion :Ft_S2, :StandardGravity do |v| "3.108094882748799e-2 * #{v}" end
conversion :Gal, :StandardGravity do |v| "1.0197162129779283e-3 * #{v}" end

# To Gal
conversion :Meter_S2, :Gal do |v| "100 * #{v}" end
conversion :Ft_S2, :Gal do |v| "30.48 * #{v}" end
conversion :StandardGravity, :Gal do |v| "980.665 * #{v}" end
