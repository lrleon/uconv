physical_quantity :CollisionType do
  symbol "CT"
  latex "CT"
  description "Fixture for type name collision validation"
end

unit :CollisionType do
  symbol "ctu"
  latex "ctu"
  description "Unit with colliding type name"
  quantity :CollisionType
  range 0..10
end
