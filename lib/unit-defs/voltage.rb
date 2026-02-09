physical_quantity :Voltage do
  symbol "U"
  latex "U"
  description "Electric potential difference"
end

unit :Volt do
  symbol "V"
  latex "V"
  description "SI unit of electric potential"
  quantity :Voltage
  range 0..1e7
end

unit :MilliVolt do
  symbol "mV"
  latex "mV"
  description "One thousandth of a volt"
  quantity :Voltage
  range 0..1e10
end

unit :KiloVolt do
  symbol "kV"
  latex "kV"
  description "One thousand volts"
  quantity :Voltage
  range 0..1e4
end

unit :MegaVolt do
  symbol "MV"
  latex "MV"
  description "One million volts"
  quantity :Voltage
  range 0..10
end

# To Volt
conversion :MilliVolt, :Volt do |v| "1e-3 * #{v}" end
conversion :KiloVolt, :Volt do |v| "1000 * #{v}" end
conversion :MegaVolt, :Volt do |v| "1e6 * #{v}" end

# To MilliVolt
conversion :Volt, :MilliVolt do |v| "1000 * #{v}" end
conversion :KiloVolt, :MilliVolt do |v| "1e6 * #{v}" end
conversion :MegaVolt, :MilliVolt do |v| "1e9 * #{v}" end

# To KiloVolt
conversion :Volt, :KiloVolt do |v| "1e-3 * #{v}" end
conversion :MilliVolt, :KiloVolt do |v| "1e-6 * #{v}" end
conversion :MegaVolt, :KiloVolt do |v| "1000 * #{v}" end

# To MegaVolt
conversion :Volt, :MegaVolt do |v| "1e-6 * #{v}" end
conversion :MilliVolt, :MegaVolt do |v| "1e-9 * #{v}" end
conversion :KiloVolt, :MegaVolt do |v| "1e-3 * #{v}" end
