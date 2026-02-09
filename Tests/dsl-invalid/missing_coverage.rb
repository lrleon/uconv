physical_quantity :LengthCoverage do
  symbol "LC"
  latex "LC"
  description "Fixture for missing conversion coverage validation"
end

unit :MeterCoverage do
  symbol "mc"
  latex "mc"
  description "Unit A"
  quantity :LengthCoverage
  range 0..100
end

unit :FootCoverage do
  symbol "fc"
  latex "fc"
  description "Unit B"
  quantity :LengthCoverage
  range 0..300
end

conversion :MeterCoverage, :FootCoverage do |v|
  "3.28083989501312 * #{v}"
end
