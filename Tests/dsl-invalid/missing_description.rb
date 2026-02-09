physical_quantity :QDescription do
  symbol "QD"
  latex "QD"
end

unit :UnitWithDescription do
  symbol "uwd"
  latex "uwd"
  description "Helper unit"
  quantity :QDescription
  range 0..10
end
