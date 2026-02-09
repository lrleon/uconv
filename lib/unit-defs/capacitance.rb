physical_quantity :Capacitance do
  symbol "Ce"
  latex "C"
  description "Ability of a system to store electric charge"
end

unit :Farad do
  symbol "F"
  latex "F"
  description "SI unit of capacitance"
  quantity :Capacitance
  range 0..1e3
end

unit :MilliFarad do
  symbol "mF"
  latex "mF"
  description "One thousandth of a farad"
  quantity :Capacitance
  range 0..1e6
end

unit :MicroFarad do
  symbol "uF"
  latex "\\mu F"
  description "One millionth of a farad"
  quantity :Capacitance
  range 0..1e9
end

unit :NanoFarad do
  symbol "nF"
  latex "nF"
  description "One billionth of a farad"
  quantity :Capacitance
  range 0..1e12
end

unit :PicoFarad do
  symbol "pF"
  latex "pF"
  description "One trillionth of a farad"
  quantity :Capacitance
  range 0..1e15
end

# To Farad
conversion :MilliFarad, :Farad do |v| "1e-3 * #{v}" end
conversion :MicroFarad, :Farad do |v| "1e-6 * #{v}" end
conversion :NanoFarad, :Farad do |v| "1e-9 * #{v}" end
conversion :PicoFarad, :Farad do |v| "1e-12 * #{v}" end

# To MilliFarad
conversion :Farad, :MilliFarad do |v| "1e3 * #{v}" end
conversion :MicroFarad, :MilliFarad do |v| "1e-3 * #{v}" end
conversion :NanoFarad, :MilliFarad do |v| "1e-6 * #{v}" end
conversion :PicoFarad, :MilliFarad do |v| "1e-9 * #{v}" end

# To MicroFarad
conversion :Farad, :MicroFarad do |v| "1e6 * #{v}" end
conversion :MilliFarad, :MicroFarad do |v| "1e3 * #{v}" end
conversion :NanoFarad, :MicroFarad do |v| "1e-3 * #{v}" end
conversion :PicoFarad, :MicroFarad do |v| "1e-6 * #{v}" end

# To NanoFarad
conversion :Farad, :NanoFarad do |v| "1e9 * #{v}" end
conversion :MilliFarad, :NanoFarad do |v| "1e6 * #{v}" end
conversion :MicroFarad, :NanoFarad do |v| "1e3 * #{v}" end
conversion :PicoFarad, :NanoFarad do |v| "1e-3 * #{v}" end

# To PicoFarad
conversion :Farad, :PicoFarad do |v| "1e12 * #{v}" end
conversion :MilliFarad, :PicoFarad do |v| "1e9 * #{v}" end
conversion :MicroFarad, :PicoFarad do |v| "1e6 * #{v}" end
conversion :NanoFarad, :PicoFarad do |v| "1e3 * #{v}" end
