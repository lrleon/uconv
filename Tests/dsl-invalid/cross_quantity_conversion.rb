physical_quantity :LengthX do
  symbol "LX"
  latex "LX"
  description "Length fixture"
end

physical_quantity :TimeX do
  symbol "TX"
  latex "TX"
  description "Time fixture"
end

unit :MeterX do
  symbol "mx"
  latex "mx"
  description "Length unit fixture"
  quantity :LengthX
  range 0..100
end

unit :SecondX do
  symbol "sx"
  latex "sx"
  description "Time unit fixture"
  quantity :TimeX
  range 0..100
end

conversion :MeterX, :SecondX do |v|
  v
end
