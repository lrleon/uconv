# Units definitions and their conversion library

## Purpose
	
`uconv` is a C++ library that allows units definitions and conversions
between different physical units through simple classes for defining
and handling physical quantities, units measuring them and quantities
related to the units with transparent conversions. 

### Physical Quantities

A physical quantity is defined with the macro 

    Declare_Physical_Unit(Physical_Quantity_Class_Name, 
	                      "Unit Symbol", "Unit LaTeX symbol",
						  "description");
						  
This macro declares a class defining a physical quantity. For example,
we can define class named `Temperature`, around which temperature units
would be grouped, as follows:

    Declare_Physical_Quantity(Temperature, "T", "T",
			  "Average thermal energy of the particles in a substance");
			  
### Units Definition

A new unit is defined with the macro

    Declare_Unit(Unit_Class_Name, "Unit symbol", "LaTeX symbol",
                 "description", Physical_Quantity, 
                 min-value, max-value);
				 
This macro declares a class that defines a new unit related to
`Physical_Quantity' class which should be previously already
declared. `min-value` and `max-value` are doubles defining the lower
and upper bounds of the unit.

As example, let us consider a `Fahrenheit` as class name that defines
the known temperature unit:

    Declare_Unit(Fahrenheit, "degF", "\\degree{F}", 
	     "Scale based on brine freezing (0) and boiling point (100)",
	     Temperature, -459.67, 750);

Since LaTeX math mode commands often start by backslash, you must
escape each backslash belonging to LaTeX expression. This is the
reason for which you see two backslashes in the string that defines
the LaTeX symbol.

### Defining Unit Conversions

Unit conversion is relatively very easy if you use the
`Declare_Conversion` macro whose syntax is as follows:

    Declare_Conversion(Source_Unit_Class_Name, 
	                   Target_Unit_Class_Name, parameter-name)
					   
This macro declares a function signature to perform the conversion of
a quantity expressed in `Source_Unit_Class_Name` towards
`Target_Unit_Class_Name` whose parameter is a double and returns a
double corresponding to the converted value. Next of using of
`Declare_Conversion`, it usually writes the function conversion body
which implements the conversion. For example, for converting from
`Fahrenheit` to `Celsius` you might write is thus:

    Declare_Conversion(Fahrenheit, Celsius, t) { return (t - 32) / 1.8; }

`Fahrenheit` and `Celsius` class names must already be defined. The
parameter `t` is a double and in the function body (between `{}`) is
written the conversion.

### Defining and Using Quantities

There are two ways for defining a quantity with its unit, everyone
with its own class:

1. `Quantity<Unit_Class_Name>`: a quantity whose unit is known in
   compiling time.
   
2. `VtlQuantity`: a quantity whose unit is known in run time.

#### `Quantity` class

`Quantity<Unit_Class_Name>` is designed for dealing units and its
conversions in compiling time, without need of lookups in run time. In
addition, the template fashion directly indicates the unit that is
been used.

As example, let us consider the following function:

    Quantity<Km_h> speed(const Quantity<Meter> & distance,
	                     const Quantity<Hour> & time)
    {
      Quantity<Meter_h> ret_val = distance.raw() / time.raw();
	  return ret_val;
    }
	
The function computes the speed given the traversed distance and the
lasted time. Distance is measured in meters and time in
hours. However, conditioned to the existence of a conversion function,
the distance and time could be in different units, kilometers or
seconds, for example. So, you could have some like this:

    Quantity<Kilometer> dist = 100;
	Quantity<Second> t = 3600;
	
	Quantity<Meter_s> s = speed(dist, t);
	
It is very important to understand everything that happens in the last
line. First, since the `speed()` function was designed for handling
meters and hours, the conversions form meters to kilometers and from
seconds to hours are performed. So, at the beginning of the `speed()`
function, the `distance` and `time` parameters are already in meters
and hours respectively. 

Second, the return value of `speed()` function is a `Quantity` whose
unit is `Km_h` (kilometers per hour) but the computation is done in
`Meter_h` (meters per hour). It is logic to define the result in
meters per hours because this is the unit that fits with the received
parameters. However the return value was declared in `Km_h`
(kilometers per hour), which should not pose any problem if the
conversion from `Meter_s` towards `Km_h` has been defined. 

Finally, it is time to mention the `raw()` method, which simply
removes the unit and returns a double. This is very important to
notice because if you performed some such as this:

    Quantity<Meter_h> ret_val = distance / time;
	
Then the library would try to find a unit that combines `Meter` and
`Second` units in the division operation. Such kind of unit is called
*compounded* unit and it could be defined with `Declare_Compound_Unit`
macro in this way:

    Declare_Compound_Unit(Meter_h, "Mt/s", "meters per second",
	                      Speed, 0, 299792458, Meter, Second);
						  
Compound units could be very useful to validate. However, they require
to define many more conversions and especially to know the unit
bounds, which increases the complexity. For this reason, it could be
preferable to directly define speed units without indicating that they
are compounded. Thus, in the example, we remove the units with the
`raw()` method, next we perform the division, and finally we build a
`Quantity<Meter_h>` object to store the result and express its unit.

#### `VltQuantity` class

`Quantity` class is very adequate for defining computations without
worry for the entry units. Computations reflecting a physical
phenomenon could be defined in a natural way, directly expressed in
their original units.  The `speed()` function example clearly shows
this kind of independence. Therefore, to the extent possible, we
strongly advice to use `Quantity` class rather than `VtlQuantity`
because it is safer and faster.

However, there are situations where it is not possible or it is not
desirable to know the units in which the computations will be
expressed. Consider, for instance, to incorporate new operations in
running time, some such like a new formula. 

### Defining bounds tolerance



## Integration

### Requirements

- Aleph-w library, which can be downloaded from
  <https://github.com/lrleon/Aleph-w>. 

- Niels Lohmann (nlohmann) json library, which can be downloaded from 
  <https://github.com/nlohmann/json>.

`uconv` has only been tested on Linux systems, but it is supposed to
run without problems on other systems where Aleph-w library is
installed. 

### Building

#### The `units-list.H` header file

#### Building the library

## Licence


