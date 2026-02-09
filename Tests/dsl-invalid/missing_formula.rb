physical_quantity :QFormula do
  symbol "QF"
  latex "QF"
  description "Fixture for missing conversion formula validation"
end

unit :UnitFormulaA do
  symbol "ufa"
  latex "ufa"
  description "Unit A"
  quantity :QFormula
  range 0..10
end

unit :UnitFormulaB do
  symbol "ufb"
  latex "ufb"
  description "Unit B"
  quantity :QFormula
  range 0..10
end

conversion :UnitFormulaA, :UnitFormulaB
