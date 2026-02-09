physical_quantity :FlowRate do
  symbol "Q"
  latex "Q"
  description "Volume rate of some fluid flow that is transported through a given cross-sectional area"
end

unit :BPD do
  symbol "bpd"
  latex "bpd"
  description "Volume rate measured in barrels per day"
  quantity :FlowRate
  range 0..1e10
end

unit :GPM do
  symbol "gpm"
  latex "gpm"
  description "Volume rate measured in U.S. Gallon Per Minute"
  quantity :FlowRate
  range 0..291666666.667
end

unit :CMD do
  symbol "cmd"
  latex "cmd"
  description "Volume rate measured in cubic meter per day"
  quantity :FlowRate
  range 0..1589872949.28
end

unit :CMS do
  symbol "cms"
  latex "cms"
  description "Volume rate measured in cubic meter per second"
  quantity :FlowRate
  range 0..18401.3072833
end

# To BPD
conversion :GPM, :BPD do |v| "34.2857142857 * #{v}" end
conversion :CMD, :BPD do |v| "6.28981077043 * #{v}" end
conversion :CMS, :BPD do |v| "543439.650565 * #{v}" end

# To GPM
conversion :BPD, :GPM do |v| "2.91666666667e-2 * #{v}" end
conversion :CMD, :GPM do |v| "0.183452814138 * #{v}" end
conversion :CMS, :GPM do |v| "15850.3231415 * #{v}" end

# To CMD
conversion :BPD, :CMD do |v| "0.158987294928 * #{v}" end
conversion :GPM, :CMD do |v| "5.45099296896 * #{v}" end
conversion :CMS, :CMD do |v| "86400 * #{v}" end

# To CMS
conversion :BPD, :CMS do |v| "1.84013072833e-6 * #{v}" end
conversion :CMD, :CMS do |v| "1.15740740741e-5 * #{v}" end
conversion :GPM, :CMS do |v| "0.0000630901964 * #{v}" end
