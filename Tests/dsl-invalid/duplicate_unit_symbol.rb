physical_quantity :QDupSymbol do
  symbol "QDS"
  latex "QDS"
  description "Fixture for duplicate unit symbol validation"
end

unit :UnitDupSymbolA do
  symbol "dup"
  latex "dupA"
  description "Unit A"
  quantity :QDupSymbol
  range 0..10
end

unit :UnitDupSymbolB do
  symbol "dup"
  latex "dupB"
  description "Unit B"
  quantity :QDupSymbol
  range 0..10
end
