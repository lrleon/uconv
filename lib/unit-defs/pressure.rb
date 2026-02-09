physical_quantity :Pressure do
  symbol "P"
  latex "P"
  description "Pressure is the force applied perpendicular to the surface of an object per unit area over which that force is distributed"
end

unit :Bar do
  symbol "bar"
  latex "bar"
  description "A bar is a metric measurement unit of pressure. One bar is equivalent to ten newtons (N) per square centimeter (cm2)"
  quantity :Pressure
  range 0..2068.43
end

unit :Pascal do
  symbol "Pa"
  latex "Pa"
  description "The pascal is the SI derived unit of pressure used to quantify internal pressure, stress, Young's modulus and ultimate tensile strength. It is defined as one newton per square metre."
  quantity :Pressure
  range 0..206843405.31
end

unit :kPascal do
  symbol "kPa"
  latex "kPa"
  description "a kPascal is a common multiple unit of the pascal 1 kPa = 1000 Pa,"
  quantity :Pressure
  range 0..206843.41
end

unit :mPascal do
  symbol "MPa"
  latex "MPa"
  description "a MPascal is a common multiple unit of the pascal 1 MPa = 1000000 Pa,"
  quantity :Pressure
  range 0..206.843410
end

unit :psia do
  symbol "psia"
  latex "psia"
  description "Pounds per square inch absolute (psia) is used to make it clear that the pressure is relative to a vacuum rather than the ambient atmospheric pressure. Since atmospheric pressure at sea level is around 14.7 psi"
  quantity :Pressure
  range 0..29985.3
end

unit :psig do
  symbol "psig"
  latex "psig"
  description "Pound-force per square inch is a unit of pressure or of stress based on avoirdupois units. It is the pressure resulting from a force of one pound-force applied to an area of one square inch"
  quantity :Pressure
  range -14.69594877551..30000
end

unit :Atmosphere do
  symbol "atm"
  latex "atm"
  description "Pound-force per square inch is a unit of pressure or of stress based on avoirdupois units. It is the pressure resulting from a force of one pound-force applied to an area of one square inch"
  quantity :Pressure
  range 0..2041.39
end

# To Pascal
conversion :Atmosphere, :Pascal do |v| "#{v} * 101324.99658" end
conversion :Bar, :Pascal do |v| "#{v} * 100000.0" end
conversion :psia, :Pascal do |v| "#{v} * 6894.757293178308" end
conversion :psig, :Pascal do |v| "(#{v} + 14.695948775) * 6894.757293178308" end
conversion :kPascal, :Pascal do |v| "#{v} * 1e3" end
conversion :mPascal, :Pascal do |v| "#{v} * 1e6" end

# To Atmosphere
conversion :Bar, :Atmosphere do |v| "#{v} * 0.986923267" end
conversion :Pascal, :Atmosphere do |v| "#{v} * 9.86923267e-6" end
conversion :kPascal, :Atmosphere do |v| "#{v} * 9.86923267e-3" end
conversion :psia, :Atmosphere do |v| "#{v} / 14.69594877551" end
conversion :psig, :Atmosphere do |v| "(#{v} + 14.69594877551) / 14.69594877551" end
conversion :mPascal, :Atmosphere do |v| "unit_convert<Pascal, Atmosphere>(unit_convert<mPascal, Pascal>(#{v}))" end

# To Bar
conversion :Atmosphere, :Bar do |v| "#{v} * 1.0132499658" end
conversion :Pascal, :Bar do |v| "#{v} * 1.0e-5" end
conversion :kPascal, :Bar do |v| "#{v} * 1.0e-2" end
conversion :psia, :Bar do |v| "#{v} * 0.0689475729" end
conversion :psig, :Bar do |v| "(#{v} + 14.695948775) * 0.0689475729" end
conversion :mPascal, :Bar do |v| "unit_convert<Pascal, Bar>(unit_convert<mPascal, Pascal>(#{v}))" end

# To kPascal
conversion :Atmosphere, :kPascal do |v| "#{v} * 101.32499658" end
conversion :Bar, :kPascal do |v| "#{v} * 100.0000" end
conversion :psia, :kPascal do |v| "#{v} * 6.894757293178308" end
conversion :psig, :kPascal do |v| "(#{v} + 14.695948775) * 6.894757293178308" end
conversion :Pascal, :kPascal do |v| "#{v} / 1000" end
conversion :mPascal, :kPascal do |v| "#{v} * 1000" end

# To mPascal
conversion :Atmosphere, :mPascal do |v| "#{v} * 0.10132499658" end
conversion :Bar, :mPascal do |v| "#{v} * 0.1" end
conversion :psia, :mPascal do |v| "#{v} * 6.894757293178308e-3" end
conversion :psig, :mPascal do |v| "((#{v} + 14.695948775) * 6.894757293178308) / 1000" end
conversion :Pascal, :mPascal do |v| "#{v} / 1e6" end
conversion :kPascal, :mPascal do |v| "#{v} / 1e3" end

# To psia
conversion :Atmosphere, :psia do |v| "#{v} * 14.695948775" end
conversion :Bar, :psia do |v| "#{v} * 14.503773773" end
conversion :Pascal, :psia do |v| "#{v} * 1.4503773773e-4" end
conversion :kPascal, :psia do |v| "#{v} * 1.4503773773e-1" end
conversion :psig, :psia do |v| "#{v} + 14.695948775" end
conversion :mPascal, :psia do |v| "unit_convert<Pascal, psia>(unit_convert<mPascal, Pascal>(#{v}))" end

# To psig
conversion :psia, :psig do |v| "#{v} - 14.695948775" end
conversion :Atmosphere, :psig do |v| "#{v} * 14.695948775 - 14.695948775" end
conversion :Bar, :psig do |v| "#{v} * 14.503773773 - 14.695948775" end
conversion :Pascal, :psig do |v| "#{v} * 1.4503773773e-4 - 14.695948775" end
conversion :kPascal, :psig do |v| "#{v} * 1.4503773773e-1 - 14.695948775" end
conversion :mPascal, :psig do |v| "unit_convert<Pascal, psig>(unit_convert<mPascal, Pascal>(#{v}))" end
