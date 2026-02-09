physical_quantity :QDupConv do
  symbol "QDC"
  latex "QDC"
  description "Fixture for duplicate conversion pair validation"
end

unit :DupConvA do
  symbol "dca"
  latex "dca"
  description "Unit A"
  quantity :QDupConv
  range 0..10
end

unit :DupConvB do
  symbol "dcb"
  latex "dcb"
  description "Unit B"
  quantity :QDupConv
  range 0..10
end

conversion :DupConvA, :DupConvB do |v|
  v
end

conversion :DupConvA, :DupConvB do |v|
  "2.0 * #{v}"
end

conversion :DupConvB, :DupConvA do |v|
  "0.5 * #{v}"
end
