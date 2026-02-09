physical_quantity :Volume do
  symbol "Vol"
  latex "V"
  description "Three-dimensional space occupied by matter"
end

unit :CubicMeter do
  symbol "m3"
  latex "m^{3}"
  description "SI unit of volume"
  quantity :Volume
  range 0..1e9
end

unit :Liter do
  symbol "L"
  latex "L"
  description "One thousandth of a cubic meter"
  quantity :Volume
  range 0..1e12
end

unit :USGallon do
  symbol "galUS"
  latex "gal_{US}"
  description "US liquid gallon"
  quantity :Volume
  range 0..2.641720523581484e11
end

unit :Barrel do
  symbol "bbl"
  latex "bbl"
  description "Oil barrel (42 US gallons)"
  quantity :Volume
  range 0..6.289810770432105e9
end

# To CubicMeter
conversion :Liter, :CubicMeter do |v| "1e-3 * #{v}" end
conversion :USGallon, :CubicMeter do |v| "3.785411784e-3 * #{v}" end
conversion :Barrel, :CubicMeter do |v| "0.158987294928 * #{v}" end

# To Liter
conversion :CubicMeter, :Liter do |v| "1000 * #{v}" end
conversion :USGallon, :Liter do |v| "3.785411784 * #{v}" end
conversion :Barrel, :Liter do |v| "158.987294928 * #{v}" end

# To USGallon
conversion :CubicMeter, :USGallon do |v| "264.1720523581484 * #{v}" end
conversion :Liter, :USGallon do |v| "0.2641720523581484 * #{v}" end
conversion :Barrel, :USGallon do |v| "42 * #{v}" end

# To Barrel
conversion :CubicMeter, :Barrel do |v| "6.289810770432105 * #{v}" end
conversion :Liter, :Barrel do |v| "6.289810770432105e-3 * #{v}" end
conversion :USGallon, :Barrel do |v| "#{v} / 42" end
