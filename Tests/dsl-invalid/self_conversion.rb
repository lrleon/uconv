physical_quantity :QSelf do
  symbol "QS"
  latex "QS"
  description "Fixture for self conversion validation"
end

unit :UnitSelf do
  symbol "us"
  latex "us"
  description "Single unit"
  quantity :QSelf
  range 0..10
end

conversion :UnitSelf, :UnitSelf do |v|
  v
end
