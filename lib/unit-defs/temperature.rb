physical_quantity :Temperature do
  symbol "T"
  latex "T"
  description "Average thermal energy of the particles in a substance"
end

unit :Kelvin do
  symbol "degK"
  latex "K"
  description "Absolute scale where the zero is the lowest temperature"
  quantity :Temperature
  range 0..672.03886667
end

unit :Celsius do
  symbol "degC"
  latex "\\degree{C}"
  description "Scale based on water freezing (0) and boiling point (100)"
  quantity :Temperature
  range -273.15..398.88888889
end

unit :Fahrenheit do
  symbol "degF"
  latex "\\degree{F}"
  description "Scale based on brine freezing (0) and boiling point (100)"
  quantity :Temperature
  range -459.67..750
end

unit :Rankine do
  symbol "degR"
  latex "\\degree{R}"
  description "Absolute scale of temperature"
  quantity :Temperature
  range 0..1209.67
end

# To Fahrenheit
conversion :Kelvin, :Fahrenheit do |t| "1.8 * #{t} - 459.67" end
conversion :Celsius, :Fahrenheit do |t| "1.8 * #{t} + 32" end
conversion :Rankine, :Fahrenheit do |t| "#{t} - 459.67" end

# To Celsius
conversion :Rankine, :Celsius do |t| "(#{t} - 491.67) / 1.8" end
conversion :Kelvin, :Celsius do |t| "#{t} - 273.15" end
conversion :Fahrenheit, :Celsius do |t| "(#{t} - 32) / 1.8" end

# To Rankine
conversion :Fahrenheit, :Rankine do |t| "#{t} + 459.67" end
conversion :Celsius, :Rankine do |t| "(#{t} + 273.15) * 1.8" end
conversion :Kelvin, :Rankine do |t| "1.8 * #{t}" end

# To Kelvin
conversion :Fahrenheit, :Kelvin do |t| "(#{t} + 459.67) / 1.8" end
conversion :Rankine, :Kelvin do |t| "#{t} / 1.8" end
conversion :Celsius, :Kelvin do |t| "#{t} + 273.15" end
