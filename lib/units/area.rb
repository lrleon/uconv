physical_quantity :Area do
  symbol "A"
  latex "A"
  description "extent of a two-dimensional figure or shape"
end

unit :Feet2 do
  symbol "ft2"
  latex "ft2"
  description "feet square"
  quantity :Area
  range 0..1e7
end

unit :Inch2 do
  symbol "in2"
  latex "in2"
  description "inch square"
  quantity :Area
  range 0..12*1e7
end

conversion :Feet2, :Inch2 do |a| "#{a}/12" end
conversion :Inch2, :Feet2 do |a| "12*#{a}" end
