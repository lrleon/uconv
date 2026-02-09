# Physical Quantities
physical_quantity :Length do
  symbol "L"
  latex "L"
  description "The length is the measurement or extent of something. It may represent reservoir thickness, drainage radius, well radius, etc."
end

# Units
unit :foot do
  symbol "ft"
  latex "ft"
  description "The length measured in feet"
  quantity :Length
  range 0..98425.1968503937
end

unit :inch do
  symbol "in"
  latex "in"
  description "The length measured in inches"
  quantity :Length
  range 0..1181102.36220472
end

unit :meter do
  symbol "m"
  latex "m"
  description "The length measured in meters"
  quantity :Length
  range 0..30000
end

unit :yard do
  symbol "yd"
  latex "yd"
  description "The length measured in yards"
  quantity :Length
  range 0..32808.3989501312
end

# Conversions

# To foot
conversion :inch, :foot do |v| "8.3333333333333333e-2 * #{v}" end
conversion :meter, :foot do |v| "3.28083989501 * #{v}" end
conversion :yard, :foot do |v| "3 * #{v}" end

# To inch
conversion :foot, :inch do |v| "12 * #{v}" end
conversion :meter, :inch do |v| "39.3700787402 * #{v}" end
conversion :yard, :inch do |v| "36 * #{v}" end

# To meter
conversion :foot, :meter do |v| "0.3048 * #{v}" end
conversion :inch, :meter do |v| "0.0254 * #{v}" end
conversion :yard, :meter do |v| "0.9144 * #{v}" end

# To yard
conversion :foot, :yard do |v| "0.33333333333333337 * #{v}" end
conversion :inch, :yard do |v| "0.027777777777777776 * #{v}" end
conversion :meter, :yard do |v| "1.0936132983377078 * #{v}" end
