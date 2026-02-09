physical_quantity :QLatex do
  symbol "QL"
  latex "QL"
  description "Fixture for missing latex validation"
end

unit :UnitMissingLatex do
  symbol "uml"
  description "Unit with missing latex"
  quantity :QLatex
  range 0..10
end
