physical_quantity :QParse do
  symbol "QP"
  latex "QP"
  description "Fixture that triggers a parser error"
end

unit :UnitParseError do
  symbol "upe"
  latex "upe"
  description "Broken fixture"
  quantity :QParse
  range 0..10
# Intentionally missing `end`
