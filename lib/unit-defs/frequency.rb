physical_quantity :Frequency do
  symbol "f"
  latex "\\nu"
  description "Number of occurrences of a repeating event per unit time"
end

unit :Hertz do
  symbol "Hz"
  latex "Hz"
  description "Unit of frequency in the International System of Units (SI) and is defined as one cycle per second"
  quantity :Frequency
  range 0..120
end

unit :Revolution_per_minute do
  symbol "RPM"
  latex "RPM"
  description "Unit of frequency and is defined as revolution (cycle) per minute"
  quantity :Frequency
  range 0..7200
end

# To Revolution_per_minute
conversion :Hertz, :Revolution_per_minute do |v| "60 * #{v}" end

# To Hertz
conversion :Revolution_per_minute, :Hertz do |v| "1.66666666666666667e-2 * #{v}" end
