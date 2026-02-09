physical_quantity :QNonNumericRange do
  symbol "QNNR"
  latex "QNNR"
  description "Fixture for non numeric range validation"
end

unit :UnitNonNumericRange do
  symbol "unnr"
  latex "unnr"
  description "Unit with non numeric range"
  quantity :QNonNumericRange
  range "a".."z"
end
