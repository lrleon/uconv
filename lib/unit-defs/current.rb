physical_quantity :Current do
  symbol "I"
  latex "I"
  description "Flow of electrical charge"
end

unit :Ampere do
  symbol "amp"
  latex "amp"
  description "One coulomb per second"
  quantity :Current
  range 0..1000
end
