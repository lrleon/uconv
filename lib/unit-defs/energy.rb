physical_quantity :Energy do
  symbol "E"
  latex "E"
  description "Capacity to do work"
end

unit :Joule do
  symbol "J"
  latex "J"
  description "SI unit of energy"
  quantity :Energy
  range 0..1e12
end

unit :KiloJoule do
  symbol "kJ"
  latex "kJ"
  description "One thousand joules"
  quantity :Energy
  range 0..1e9
end

unit :WattHour do
  symbol "Wh"
  latex "Wh"
  description "Energy of one watt sustained for one hour"
  quantity :Energy
  range 0..2.7777777777777778e8
end

unit :BTU do
  symbol "BTU"
  latex "BTU"
  description "British thermal unit"
  quantity :Energy
  range 0..9.478171203132992e8
end

# To Joule
conversion :KiloJoule, :Joule do |v| "1000 * #{v}" end
conversion :WattHour, :Joule do |v| "3600 * #{v}" end
conversion :BTU, :Joule do |v| "1055.05585262 * #{v}" end

# To KiloJoule
conversion :Joule, :KiloJoule do |v| "1e-3 * #{v}" end
conversion :WattHour, :KiloJoule do |v| "3.6 * #{v}" end
conversion :BTU, :KiloJoule do |v| "1.05505585262 * #{v}" end

# To WattHour
conversion :Joule, :WattHour do |v| "2.7777777777777778e-4 * #{v}" end
conversion :KiloJoule, :WattHour do |v| "0.2777777777777778 * #{v}" end
conversion :BTU, :WattHour do |v| "0.2930710701722222 * #{v}" end

# To BTU
conversion :Joule, :BTU do |v| "9.478171203132992e-4 * #{v}" end
conversion :KiloJoule, :BTU do |v| "0.9478171203132992 * #{v}" end
conversion :WattHour, :BTU do |v| "3.412141633127942 * #{v}" end
