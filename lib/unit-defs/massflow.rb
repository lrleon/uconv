physical_quantity :MassFlow do
  symbol "m_dot"
  latex "\\dot{m}"
  description "Mass transported per unit time"
end

unit :Kg_S do
  symbol "kg/s"
  latex "kg/s"
  description "Mass flow in kilograms per second"
  quantity :MassFlow
  range 0..1e7
end

unit :Kg_H do
  symbol "kg/h"
  latex "kg/h"
  description "Mass flow in kilograms per hour"
  quantity :MassFlow
  range 0..3.6e10
end

unit :Lb_S do
  symbol "lb/s"
  latex "lb/s"
  description "Mass flow in pounds mass per second"
  quantity :MassFlow
  range 0..2.2046226218487757e7
end

unit :Lb_H do
  symbol "lb/h"
  latex "lb/h"
  description "Mass flow in pounds mass per hour"
  quantity :MassFlow
  range 0..7.936641438655593e10
end

unit :Tonne_Day do
  symbol "t/d"
  latex "t/d"
  description "Mass flow in metric tonnes per day"
  quantity :MassFlow
  range 0..8.64e8
end

# To Kg_S
conversion :Kg_H, :Kg_S do |v| "2.777777777777778e-4 * #{v}" end
conversion :Lb_S, :Kg_S do |v| "0.45359237 * #{v}" end
conversion :Lb_H, :Kg_S do |v| "1.2599788055555556e-4 * #{v}" end
conversion :Tonne_Day, :Kg_S do |v| "1.1574074074074073e-2 * #{v}" end

# To Kg_H
conversion :Kg_S, :Kg_H do |v| "3600 * #{v}" end
conversion :Lb_S, :Kg_H do |v| "1632.932532 * #{v}" end
conversion :Lb_H, :Kg_H do |v| "0.45359237 * #{v}" end
conversion :Tonne_Day, :Kg_H do |v| "41.666666666666664 * #{v}" end

# To Lb_S
conversion :Kg_S, :Lb_S do |v| "2.2046226218487757 * #{v}" end
conversion :Kg_H, :Lb_S do |v| "6.123951727357711e-4 * #{v}" end
conversion :Lb_H, :Lb_S do |v| "2.777777777777778e-4 * #{v}" end
conversion :Tonne_Day, :Lb_S do |v| "2.5516465530657124e-2 * #{v}" end

# To Lb_H
conversion :Kg_S, :Lb_H do |v| "7936.641438655593 * #{v}" end
conversion :Kg_H, :Lb_H do |v| "2.2046226218487757 * #{v}" end
conversion :Lb_S, :Lb_H do |v| "3600 * #{v}" end
conversion :Tonne_Day, :Lb_H do |v| "91.85927591036565 * #{v}" end

# To Tonne_Day
conversion :Kg_S, :Tonne_Day do |v| "86.4 * #{v}" end
conversion :Kg_H, :Tonne_Day do |v| "2.4e-2 * #{v}" end
conversion :Lb_S, :Tonne_Day do |v| "39.190380768000004 * #{v}" end
conversion :Lb_H, :Tonne_Day do |v| "1.088621688e-2 * #{v}" end
