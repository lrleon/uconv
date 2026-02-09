physical_quantity :QRange do
  symbol "QR"
  latex "QR"
  description "Fixture for missing range validation"
end

unit :UnitMissingRange do
  symbol "umr"
  latex "umr"
  description "Unit missing range"
  quantity :QRange
end
