physical_quantity :QInvalidRange do
  symbol "QIR"
  latex "QIR"
  description "Fixture for invalid range validation"
end

unit :UnitInvalidRange do
  symbol "uir"
  latex "uir"
  description "Unit with min > max"
  quantity :QInvalidRange
  range 10..0
end
