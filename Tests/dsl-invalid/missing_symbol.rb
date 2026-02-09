physical_quantity :LengthBad do
  symbol "LB"
  latex "LB"
  description "Fixture for missing symbol validation"
end

unit :MeterBad do
  # symbol is intentionally missing
  latex "m"
  description "Broken unit fixture"
  quantity :LengthBad
  range 0..100
end
