physical_quantity :QUnknownTarget do
  symbol "QUT"
  latex "QUT"
  description "Fixture for unknown target unit validation"
end

unit :KnownUnitSource do
  symbol "kus"
  latex "kus"
  description "Known source unit"
  quantity :QUnknownTarget
  range 0..10
end

conversion :KnownUnitSource, :MissingTargetUnit do |v|
  v
end
