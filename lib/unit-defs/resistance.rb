physical_quantity :Resistance do
  symbol "R"
  latex "R"
  description "Opposition to electric current"
end

unit :Ohm do
  symbol "ohm"
  latex "\\Omega"
  description "SI unit of electrical resistance"
  quantity :Resistance
  range 0..1e9
end

unit :MilliOhm do
  symbol "mohm"
  latex "m\\Omega"
  description "One thousandth of an ohm"
  quantity :Resistance
  range 0..1e12
end

unit :KiloOhm do
  symbol "kohm"
  latex "k\\Omega"
  description "One thousand ohms"
  quantity :Resistance
  range 0..1e6
end

unit :MegaOhm do
  symbol "Mohm"
  latex "M\\Omega"
  description "One million ohms"
  quantity :Resistance
  range 0..1e3
end

# To Ohm
conversion :MilliOhm, :Ohm do |v| "1e-3 * #{v}" end
conversion :KiloOhm, :Ohm do |v| "1e3 * #{v}" end
conversion :MegaOhm, :Ohm do |v| "1e6 * #{v}" end

# To MilliOhm
conversion :Ohm, :MilliOhm do |v| "1e3 * #{v}" end
conversion :KiloOhm, :MilliOhm do |v| "1e6 * #{v}" end
conversion :MegaOhm, :MilliOhm do |v| "1e9 * #{v}" end

# To KiloOhm
conversion :Ohm, :KiloOhm do |v| "1e-3 * #{v}" end
conversion :MilliOhm, :KiloOhm do |v| "1e-6 * #{v}" end
conversion :MegaOhm, :KiloOhm do |v| "1e3 * #{v}" end

# To MegaOhm
conversion :Ohm, :MegaOhm do |v| "1e-6 * #{v}" end
conversion :MilliOhm, :MegaOhm do |v| "1e-9 * #{v}" end
conversion :KiloOhm, :MegaOhm do |v| "1e-3 * #{v}" end
