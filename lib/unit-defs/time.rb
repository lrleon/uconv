physical_quantity :Time do
  symbol "t"
  latex "t"
  description "The mythical and mysterious fourth dimension"
end

unit :day do
  symbol "day"
  latex "d"
  description "twenty four hours"
  quantity :Time
  range 0..365*24
end

unit :hour do
  symbol "h"
  latex "h"
  description "sixty minutes"
  quantity :Time
  range 0..10*365*24
end

unit :minute do
  symbol "min"
  latex "min"
  description "sixty seconds"
  quantity :Time
  range 0..10*365*24*60
end

unit :second do
  symbol "sec"
  latex "seconds"
  description "VIRGINIA"
  quantity :Time
  range 0..10*365*24*60*60
end

# To hour
conversion :day, :hour do |val| "24*#{val}" end
conversion :minute, :hour do |val| "#{val}/60" end
conversion :second, :hour do |val| "#{val}/(60*60)" end

# To minute
conversion :day, :minute do |val| "24*60*#{val}" end
conversion :hour, :minute do |val| "60*#{val}" end
conversion :second, :minute do |val| "#{val}/60" end

# To second
conversion :day, :second do |val| "24*60*60*#{val}" end
conversion :hour, :second do |val| "60*60*#{val}" end
conversion :minute, :second do |val| "60*#{val}" end

# To day
conversion :hour, :day do |val| "#{val}/24" end
conversion :minute, :day do |val| "#{val}/(24*60)" end
conversion :second, :day do |val| "#{val}/(24*60*60)" end
