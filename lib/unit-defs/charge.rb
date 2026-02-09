physical_quantity :Charge do
  symbol "Qe"
  latex "Q"
  description "Electric charge transported by current over time"
end

unit :Coulomb do
  symbol "C"
  latex "C"
  description "SI unit of electric charge"
  quantity :Charge
  range 0..1e10
end

unit :AmpereHour do
  symbol "Ah"
  latex "Ah"
  description "Charge transported by one ampere in one hour"
  quantity :Charge
  range 0..2.777777777777778e6
end

unit :MilliAmpereHour do
  symbol "mAh"
  latex "mAh"
  description "One thousandth of an ampere-hour"
  quantity :Charge
  range 0..2.777777777777778e9
end

# To Coulomb
conversion :AmpereHour, :Coulomb do |v| "3600 * #{v}" end
conversion :MilliAmpereHour, :Coulomb do |v| "3.6 * #{v}" end

# To AmpereHour
conversion :Coulomb, :AmpereHour do |v| "#{v} / 3600" end
conversion :MilliAmpereHour, :AmpereHour do |v| "1e-3 * #{v}" end

# To MilliAmpereHour
conversion :Coulomb, :MilliAmpereHour do |v| "#{v} / 3.6" end
conversion :AmpereHour, :MilliAmpereHour do |v| "1000 * #{v}" end
