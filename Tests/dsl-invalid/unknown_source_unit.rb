physical_quantity :QUnknownSource do
  symbol "QUS"
  latex "QUS"
  description "Fixture for unknown source unit validation"
end

unit :KnownUnitTarget do
  symbol "kut"
  latex "kut"
  description "Known target unit"
  quantity :QUnknownSource
  range 0..10
end

conversion :MissingSourceUnit, :KnownUnitTarget do |v|
  v
end
