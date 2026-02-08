physical_quantity :Force do
  symbol "F"
  latex "F"
  description "Interaction that changes the motion of an object"
end

unit :Newton do
  symbol "N"
  latex "N"
  description "SI unit of force"
  quantity :Force
  range 0..1e9
end

unit :kNewton do
  symbol "kN"
  latex "kN"
  description "One thousand newtons"
  quantity :Force
  range 0..1e6
end

unit :PoundForce do
  symbol "lbf"
  latex "lbf"
  description "Imperial unit of force"
  quantity :Force
  range 0..2.2480894387096265e8
end

unit :Dyne do
  symbol "dyn"
  latex "dyn"
  description "CGS unit of force (1 dyn = 1e-5 N)"
  quantity :Force
  range 0..1e14
end

# To Newton
conversion :kNewton, :Newton do |v| "1000 * #{v}" end
conversion :PoundForce, :Newton do |v| "4.4482216152605 * #{v}" end
conversion :Dyne, :Newton do |v| "1e-5 * #{v}" end

# To kNewton
conversion :Newton, :kNewton do |v| "1e-3 * #{v}" end
conversion :PoundForce, :kNewton do |v| "4.4482216152605e-3 * #{v}" end
conversion :Dyne, :kNewton do |v| "1e-8 * #{v}" end

# To PoundForce
conversion :Newton, :PoundForce do |v| "0.22480894387096263 * #{v}" end
conversion :kNewton, :PoundForce do |v| "224.80894387096263 * #{v}" end
conversion :Dyne, :PoundForce do |v| "2.2480894387096265e-6 * #{v}" end

# To Dyne
conversion :Newton, :Dyne do |v| "1e5 * #{v}" end
conversion :kNewton, :Dyne do |v| "1e8 * #{v}" end
conversion :PoundForce, :Dyne do |v| "444822.16152605 * #{v}" end
