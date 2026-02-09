physical_quantity :Diameter do
  symbol "D"
  latex "D"
  description "The diameter is the measurement of a straight line passing from side to side through the center of a body or figure, especially a circle. It is used to designate the pipe size. The diameter is denoted as D."
end

unit :Foot_D do
  symbol "ft_d"
  latex "ft"
  description "The diameter measured in feet"
  quantity :Diameter
  range 8.3333333333333333e-2..25
end

unit :Inch_D do
  symbol "in_d"
  latex "in"
  description "The diameter measured in inches"
  quantity :Diameter
  range 1..300
end

unit :Meter_D do
  symbol "m_d"
  latex "m"
  description "The diameter measured in meters"
  quantity :Diameter
  range 0.0254..7.62
end

unit :Centimeter_D do
  symbol "cm"
  latex "cm"
  description "The diameter measured in centimeters"
  quantity :Diameter
  range 2.54..762
end

unit :Millimeter_D do
  symbol "mm"
  latex "mm"
  description "The diameter measured in millimeters"
  quantity :Diameter
  range 25.4..7620
end

# To Foot_D
conversion :Inch_D, :Foot_D do |v| "8.3333333333333333e-2 * #{v}" end
conversion :Meter_D, :Foot_D do |v| "3.28083989501 * #{v}" end
conversion :Centimeter_D, :Foot_D do |v| "3.28083989501e-2 * #{v}" end
conversion :Millimeter_D, :Foot_D do |v| "3.28083989501e-3 * #{v}" end

# To Inch_D
conversion :Foot_D, :Inch_D do |v| "12 * #{v}" end
conversion :Meter_D, :Inch_D do |v| "39.3700787402 * #{v}" end
conversion :Centimeter_D, :Inch_D do |v| "39.3700787402e-2 * #{v}" end
conversion :Millimeter_D, :Inch_D do |v| "39.3700787402e-3 * #{v}" end

# To Meter_D
conversion :Foot_D, :Meter_D do |v| "0.3048 * #{v}" end
conversion :Inch_D, :Meter_D do |v| "0.0254 * #{v}" end
conversion :Centimeter_D, :Meter_D do |v| "1e-2 * #{v}" end
conversion :Millimeter_D, :Meter_D do |v| "1e-3 * #{v}" end

# To Centimeter_D
conversion :Foot_D, :Centimeter_D do |v| "30.48 * #{v}" end
conversion :Inch_D, :Centimeter_D do |v| "2.54 * #{v}" end
conversion :Meter_D, :Centimeter_D do |v| "1e2 * #{v}" end
conversion :Millimeter_D, :Centimeter_D do |v| "0.1 * #{v}" end

# To Millimeter_D
conversion :Foot_D, :Millimeter_D do |v| "304.8 * #{v}" end
conversion :Inch_D, :Millimeter_D do |v| "25.4 * #{v}" end
conversion :Meter_D, :Millimeter_D do |v| "1e3 * #{v}" end
conversion :Centimeter_D, :Millimeter_D do |v| "10 * #{v}" end
