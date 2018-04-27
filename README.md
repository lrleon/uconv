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
`Physical_Quantity` class which should be previously already
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

When a conversion is required but this one has not been defined, a
compiler error will be generated.

`Quantity` object always require to know their unit. Consequently, it
is not possible to instantiate a empty `Quantity`, without a value,
because if not the boundary check could not be performed.

#### `VltQuantity` class

`Quantity` class is very adequate for defining computations without
worry for the entry units. Computations reflecting a physical
phenomenon could be defined in a natural way, directly expressed in
their original units.  The `speed()` function example clearly shows
this kind of independence. Therefore, to the extent possible, we
strongly advice to use `Quantity` class rather than `VtlQuantity`
because it is safer and faster.

However, there are situations where it is not possible or desirable to
know the units in which the computations will be expressed. Consider,
for instance, to incorporate new operations in running time, some such
like a new formula. In this case, a `Quantity` object is not
applicable because it requires to know the unit type in
compiling time. For dealing with situations like this, the
`VtlQuantity` class is provided. 

There is not so much difference between a `Quantity` and a
`Vtlquantity` object. Essentially, the main difference is that the
`Vtlquantity` constructor requires the unit as part of its parameters
(to the difference of `Quantity` that receives the unit as a template
parameter). 

The price of a `Vtlquantity` object is the possibility of a table look
up in order to find the conversion function. Apart of that, practically
use of `Quantity` and `VtlQuantity` is very similar. In fact, you can
arbitrarily combine them.

#### Mathematical operations

`uconv` export some mathematical operations.  In all operations, the
unit limits are checked. 

The main binary mathematical operators `+`, `-`, `*` and `/` are
exported. Each binary operation can receive, `Quantity`, `VtlQuantity`
or double objects. If a double is received, then it is assumed that
its unit is the same than the another operand.  `+` and `-` operators
require that both operands are in the same unit. In the case of `*`
and `/` operands, the compound unit corresponding to the result is
required.

Other wrappers to C mathematical functions are provided: `pow()`,
`exp()`, `log10()`, `sqrt()`, etc. All this functions return a double.

### Defining bounds tolerance

Since the most of conversions involve floating point operations, the
units limits are verified respect a tolerance value called epsilon. By
default, this value is `1e-6` but it can be set to any other
value. Let be `min-val` and `max-val` the limits of some unit. Then,
the limits check is done on the interval `[min-val - epsilon,
max-val + epsilon]`. Notice that without this tolerance, then we could
get an `OutOfUnitRange` exception if, for example, we convert
`min-value` to another unit and we return again on the original unit. 

### The `uconv-list.H` header file

The current way for indicating to the library which are the units is
through file inclusion in the `uconv-list.H` header file. When the
library is built, the system will search this file in order to
generate all the needed bookkeeping.

## Integration

There are two ways for integrating `uconv` to your project. The first
one is by adding your units directly to the library distribution and
building it. The second way, which is the recommended, is by building
your own library.

#### Adding units to `uconv` distribution

In order to use `uconv`, you require:

1. Include the header `uconv.H` in the places of your project using
   units and conversions.

2. Define your physical magnitudes along with their units (or reuse
   them). In order to do that, we advice to create a file for each
   physical magnitude, define it along its units and put there the
   required conversion functions.
   
3. Edit the `uconv-list.H` header file and put there header inclusions
   for everyone of your units. Here, you
   
4. Generate the `uconvlib.a` and link it to your project.

#### Building your own `libuconv.a` library


#### Usage in your project

`uconv` internally uses several tables for storing physical quantities
names, units and conversions. For this reason, it is imperative to
explicitly initialize the library. The most recommended way for doing
that with `UnitsInstancer` class, which is a singleton and that must
be called before any use of `uconv`. As general rule, we recommend to
instantiate just next the `uconv-list.H` header inclusion. Some such
this:

	# include <uconv-list.H>
	UnitsInstancer init; // or any other name that you want
	// here you could put other header inclusions

### Requirements

You will need Aleph-w library, which can be downloaded from
<https://github.com/lrleon/Aleph-w> and the Niels Lohmann (nlohmann) json
library, which can be downloaded from <https://github.com/nlohmann/json>.

In order to build

`uconv` has only been tested on Linux systems, but it is supposed to
run without problems on other systems where Aleph-w library is
installed. 

### Building the library

First, set the `ALEPHW` and `NLOHMANNJSON` environment variables to
point to the directories where `Aleph-w` and Niels Lohmann json
libraries are. Next, on the distribution directory, perform:

    xmkmf
	make Makefiles
	make depend
	
Finally, go to `lib` directory and perform 

	make 
	
This should build the file `uconlib.a` which contains the `uconv` library.

## License

Since `uconv` depends on components that are licensed GNU GPL v3,
`uconv` is also licensed on the GNU GPL v3.

See
[LICENSE](https://github.com/lrleon/uconv/blob/master/LICENSE). COPYRIGHT
(c) 2018, Ixhel Mejias, Alberto Valderrama, Fernando Montilla, Eduardo
Valderrama, Neylith Quintero, Felix Buccellato, Virginia Buccellato
and Leandro Rabindranath Leon
