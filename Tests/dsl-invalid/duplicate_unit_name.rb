physical_quantity :QDupName do
  symbol "QDN"
  latex "QDN"
  description "Fixture for duplicate unit name validation"
end

unit :UnitDupName do
  symbol "udn_a"
  latex "udn_a"
  description "First unit with duplicate name"
  quantity :QDupName
  range 0..10
end

unit :UnitDupName do
  symbol "udn_b"
  latex "udn_b"
  description "Second unit with duplicate name"
  quantity :QDupName
  range 0..10
end
