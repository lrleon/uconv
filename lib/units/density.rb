physical_quantity :Density do
  symbol "rho"
  latex "\\rho"
  description "The density of a substance is its mass per unit volume"
end

unit :Gr_cm3 do
  symbol "gr/cm3"
  latex "g/cm^{3}"
  description "unit of density declared as gr (mass in gram) per cm3 (unit volume in cubic centimeter)"
  quantity :Density
  range 0.0001..3.30
end

unit :Kg_m3 do
  symbol "kg/m3"
  latex "kg/m^{3}"
  description "unit of density declared as kg (mass in kilogram) per m3 (unit volume in cubic meter)"
  quantity :Density
  range 0.1..3300
end

unit :Kg_L do
  symbol "kg/L"
  latex "kg/L"
  description "unit of density declared as kg (mass in kilogram ) per L (unit volume in liter)"
  quantity :Density
  range 0.0001..3.30
end

unit :Lb_ft3 do
  symbol "lb/ft3"
  latex "lb/ft^{3}"
  description "unit of density declared as lb (mass in pound ) per ft3 (unit volume in cubic feet)"
  quantity :Density
  range 0.006242782..206.0117994
end

unit :Lb_Gal do
  symbol "lb/gal"
  latex "lb/gal"
  description "unit of density declared as lb (mass in pound ) per Gal (unit volume in Gallons)"
  quantity :Density
  range 0.000834538..27.5397507
end

unit :Lb_Inch3 do
  symbol "lb/inch3"
  latex "lb/in^{3}"
  description "unit of density declared as lb (mass in pound ) per inch3 (unit volume in cubic inches)"
  quantity :Density
  range 0.000003613..0.119219793
end

unit :Sg do
  symbol "sg"
  latex "water=1\\ at\\ 60\\ \\degree{F}"
  description "Specific gravity is the ratio of the density of a substance to the density of a reference substance water"
  quantity :Density
  range 0.00010009849692097025..3.303250398392018
end

# To Gr_cm3
conversion :Kg_m3, :Gr_cm3 do |v| "0.001 * #{v}" end
conversion :Kg_L, :Gr_cm3 do |v| "#{v}" end
conversion :Lb_ft3, :Gr_cm3 do |v| "0.01601846337396014 * #{v}" end
conversion :Sg, :Gr_cm3 do |v| "0.999016 * #{v}" end
conversion :Lb_Gal, :Gr_cm3 do |v| "0.119826793 * #{v}" end
conversion :Lb_Inch3, :Gr_cm3 do |v| "27.679967537 * #{v}" end

# To Kg_m3
conversion :Gr_cm3, :Kg_m3 do |v| "1000 * #{v}" end
conversion :Kg_L, :Kg_m3 do |v| "1000 * #{v}" end
conversion :Lb_ft3, :Kg_m3 do |v| "16.018463374 * #{v}" end
conversion :Sg, :Kg_m3 do |v| "999.016 * #{v}" end
conversion :Lb_Gal, :Kg_m3 do |v| "119.826792768 * #{v}" end
conversion :Lb_Inch3, :Kg_m3 do |v| "27679.898580851597 * #{v}" end

# To Kg_L
conversion :Gr_cm3, :Kg_L do |v| "#{v}" end
conversion :Kg_m3, :Kg_L do |v| "0.001 * #{v}" end
conversion :Lb_ft3, :Kg_L do |v| "0.01601846337396014 * #{v}" end
conversion :Sg, :Kg_L do |v| "0.999016 * #{v}" end
conversion :Lb_Gal, :Kg_L do |v| "0.119826792768 * #{v}" end
conversion :Lb_Inch3, :Kg_L do |v| "27.679967537 * #{v}" end

# To Sg
conversion :Gr_cm3, :Sg do |v| "#{v} / 0.999016" end
conversion :Kg_m3, :Sg do |v| "#{v} / 999.016" end
conversion :Lb_ft3, :Sg do |v| "#{v} / 62.366389027" end
conversion :Kg_L, :Sg do |v| "#{v} / 0.999016" end
conversion :Lb_Gal, :Sg do |v| "#{v} / 8.337167147" end
conversion :Lb_Inch3, :Sg do |v| "#{v} / 0.036091661" end

# To Lb_ft3
conversion :Gr_cm3, :Lb_ft3 do |v| "62.4279605761446 * #{v}" end
conversion :Kg_m3, :Lb_ft3 do |v| "0.0624279606 * #{v}" end
conversion :Kg_L, :Lb_ft3 do |v| "62.4279605761446 * #{v}" end
conversion :Sg, :Lb_ft3 do |v| "62.366389027 * #{v}" end
conversion :Lb_Gal, :Lb_ft3 do |v| "7.480525210 * #{v}" end
conversion :Lb_Inch3, :Lb_ft3 do |v| "1727.999975642 * #{v}" end

# To Lb_Gal
conversion :Kg_m3, :Lb_Gal do |v| "0.0083453790 * #{v}" end
conversion :Gr_cm3, :Lb_Gal do |v| "8.3453790000 * #{v}" end
conversion :Kg_L, :Lb_Gal do |v| "8.3453790000 * #{v}" end
conversion :Lb_ft3, :Lb_Gal do |v| "0.1336804532 * #{v}" end
conversion :Sg, :Lb_Gal do |v| "8.3371671471 * #{v}" end
conversion :Lb_Inch3, :Lb_Gal do |v| "230.9998198034 * #{v}" end

# To Lb_Inch3
conversion :Kg_m3, :Lb_Inch3 do |v| "0.0000361273 * #{v}" end
conversion :Gr_cm3, :Lb_Inch3 do |v| "0.0361272100 * #{v}" end
conversion :Kg_L, :Lb_Inch3 do |v| "0.0361272100 * #{v}" end
conversion :Lb_ft3, :Lb_Inch3 do |v| "0.0005787037 * #{v}" end
conversion :Sg, :Lb_Inch3 do |v| "0.0360910828 * #{v}" end
conversion :Lb_Gal, :Lb_Inch3 do |v| "0.0043290077 * #{v}" end
