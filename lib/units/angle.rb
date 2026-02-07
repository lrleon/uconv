physical_quantity :Angle do
  symbol "angle"
  latex "\\angle"
  description "figure formed by two rays sharing a common endpoint"
end

unit :Degree do
  symbol "deg"
  latex "\\degree"
  description "Angle measured in Degrees"
  quantity :Angle
  range -90..90
end

unit :Radian do
  symbol "rad"
  latex "rad"
  description "Angle measured in Radians"
  quantity :Angle
  range -1.5707963267948966..1.5707963267948966
end

# Conversions
conversion :Degree, :Radian do |val| "#{val}*M_PI/180" end
conversion :Radian, :Degree do |val| "#{val}*180/M_PI" end
