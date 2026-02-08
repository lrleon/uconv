physical_quantity :Mass do
  symbol "M"
  latex "M"
  description "Amount of matter in a body"
end

unit :Kilogram do
  symbol "kg"
  latex "kg"
  description "SI base unit of mass"
  quantity :Mass
  range 0..1e8
end

unit :Gram do
  symbol "g"
  latex "g"
  description "One thousandth of a kilogram"
  quantity :Mass
  range 0..1e11
end

unit :PoundMass do
  symbol "lbm"
  latex "lbm"
  description "Avoirdupois pound as mass unit"
  quantity :Mass
  range 0..2.2046226218487757e8
end

unit :MetricTon do
  symbol "t"
  latex "t"
  description "Metric ton (tonne), equal to 1000 kilograms"
  quantity :Mass
  range 0..1e5
end

# To Kilogram
conversion :Gram, :Kilogram do |v| "1e-3 * #{v}" end
conversion :PoundMass, :Kilogram do |v| "0.45359237 * #{v}" end
conversion :MetricTon, :Kilogram do |v| "1000 * #{v}" end

# To Gram
conversion :Kilogram, :Gram do |v| "1000 * #{v}" end
conversion :PoundMass, :Gram do |v| "453.59237 * #{v}" end
conversion :MetricTon, :Gram do |v| "1e6 * #{v}" end

# To PoundMass
conversion :Kilogram, :PoundMass do |v| "2.2046226218487757 * #{v}" end
conversion :Gram, :PoundMass do |v| "2.2046226218487757e-3 * #{v}" end
conversion :MetricTon, :PoundMass do |v| "2204.6226218487757 * #{v}" end

# To MetricTon
conversion :Kilogram, :MetricTon do |v| "1e-3 * #{v}" end
conversion :Gram, :MetricTon do |v| "1e-6 * #{v}" end
conversion :PoundMass, :MetricTon do |v| "4.5359237e-4 * #{v}" end
