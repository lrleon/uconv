physical_quantity :Torque do
  symbol "Tau"
  latex "\\tau"
  description "Rotational equivalent of force"
end

unit :NewtonMeter do
  symbol "N*m"
  latex "N\\cdot m"
  description "SI unit of torque"
  quantity :Torque
  range 0..1e9
end

unit :PoundFoot do
  symbol "lbf*ft"
  latex "lbf\\cdot ft"
  description "Imperial torque unit pound-force foot"
  quantity :Torque
  range 0..7.375621492772656e8
end

unit :PoundInch do
  symbol "lbf*in"
  latex "lbf\\cdot in"
  description "Imperial torque unit pound-force inch"
  quantity :Torque
  range 0..8.850745791327183e9
end

unit :KilogramForceMeter do
  symbol "kgf*m"
  latex "kgf\\cdot m"
  description "Torque unit kilogram-force meter"
  quantity :Torque
  range 0..1.0197162129779283e8
end

# To NewtonMeter
conversion :PoundFoot, :NewtonMeter do |v| "1.3558179483314004 * #{v}" end
conversion :PoundInch, :NewtonMeter do |v| "0.1129848290276167 * #{v}" end
conversion :KilogramForceMeter, :NewtonMeter do |v| "9.80665 * #{v}" end

# To PoundFoot
conversion :NewtonMeter, :PoundFoot do |v| "0.7375621492772656 * #{v}" end
conversion :PoundInch, :PoundFoot do |v| "#{v} / 12" end
conversion :KilogramForceMeter, :PoundFoot do |v| "7.233013851209894 * #{v}" end

# To PoundInch
conversion :NewtonMeter, :PoundInch do |v| "8.850745791327183 * #{v}" end
conversion :PoundFoot, :PoundInch do |v| "12 * #{v}" end
conversion :KilogramForceMeter, :PoundInch do |v| "86.79616621451873 * #{v}" end

# To KilogramForceMeter
conversion :NewtonMeter, :KilogramForceMeter do |v| "0.10197162129779283 * #{v}" end
conversion :PoundFoot, :KilogramForceMeter do |v| "0.138254954376 * #{v}" end
conversion :PoundInch, :KilogramForceMeter do |v| "1.1521246198e-2 * #{v}" end
