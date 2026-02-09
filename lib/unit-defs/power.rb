physical_quantity :Power do
  symbol "Pow"
  latex "P"
  description "power is the rate of doing work. It is the amount of energy consumed per unit time"
end

unit :HorsePower do
  symbol "hp"
  latex "hp"
  description "Unit of measurement of power hp"
  quantity :Power
  range 0..2000
end

unit :Watt do
  symbol "W"
  latex "W"
  description "Unit of measurement of power watt"
  quantity :Power
  range 0..1491399.74316
end

# To HorsePower
conversion :Watt, :HorsePower do |v| "1.3410220896e-3 * #{v}" end

# To Watt
conversion :HorsePower, :Watt do |v| "745.699871582 * #{v}" end
