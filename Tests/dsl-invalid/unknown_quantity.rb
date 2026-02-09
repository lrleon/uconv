physical_quantity :LengthOk do
  symbol "LQ"
  latex "LQ"
  description "Fixture for unknown quantity reference validation"
end

unit :MeterUnknownQuantity do
  symbol "muq"
  latex "muq"
  description "Unit points to a non-existent quantity"
  quantity :DoesNotExist
  range 0..100
end
