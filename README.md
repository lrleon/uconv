# Units definitions and their conversion library

## Purpose
	
`uconv` is a C++ library that allows to define physical quantities
along with units definitions and conversions between different units
through simple classes for defining and handling physical quantities,
units measuring them and quantities related to the units with
transparent conversions. 

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
				 
This macro declares a class that defines a new unit related to the
`Physical_Quantity` class which should be previously already
declared. `min-value` and `max-value` are doubles defining the lower
and upper bounds of the unit.

As example, let us consider `Fahrenheit` as class name that defines
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
`Target_Unit_Class_Name`, whose parameter is a double, and it returns
a double corresponding to the converted value. Next of using of
`Declare_Conversion`, the function conversion body which implements
the conversion must be written. For example, for converting from
`Fahrenheit` to `Celsius` you might write this thus:

    Declare_Conversion(Fahrenheit, Celsius, t) { return (t - 32) / 1.8; }

`Fahrenheit` and `Celsius` class names must already be defined. The
parameter `t` is a double in `Fahrenheit` and in the function body
(between `{}`) is written the conversion.

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

`uconv` export some mathematical operations. In all operations, the
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
then building the `libuconv.a` file. This way implies that you should
edit the `uconv-list.H` file and put file inclusions to your unit
definitions. The second way, which is the recommended, is to create
and manage your own `uconv-list.H` (or another name that you want) and 
building your own `libuconv.a` file (or another name that you want).

Let us suppose that your unit definitions are in `uconv-list.H`
file. First, this file must include the header `uconv.H` followed by
file inclusions to your units definitions. Some such that:

	# include <uconv.H>
	# include "units/temperature-unit.H"
	# include "units/pressure-unit.H"
	# include "units/density-unit.H"
	// so on ...
	
From the second line, each line is a file inclusion to a header
containing a physical quantity along with its units. 

You must put an inclusion for `uconv-list.H` in every place of your
project requiring to manage units. Note that you can rename
`uconv-list.H`, but you should not remove the inclusion to `uconv.H`.

Your project must be able to locate the headers `uconv.H` and
`uconv-list.H` and to link `libuconv.a` file to the every executable.

#### Building the `libuconv.a` library inside the `uconv` distribution

In this case, the recommended way is to place the units definitions
headers in the `include/units` sub directory. Once you have already
defined all your units, go to the `lib` directory and perform:

	make depend
	make all

If everything was okay, you will have `libuconv.a` file in the directory.

#### Building your own `libuconv.a` library

If you have several projects managing units, then you probably will
want to manage several and independent unit systems. In this case, you
will not probably want to build `libuconv.a` inside `uconv`
distribution because this library will contain all the units through
all your projects with the consequent waste of space and time. 

In order to manage this, you can use the script `buildunits` contained
in the `bin` directory. Its command line syntax is as follows:

    buildunits -U uconv-list-file -H path-to-uconv-header
	
Let us suppose that you have defined your unit in `my-units.H`
file. Then, you perform:

    buildunits -U my-units.H -H myproject/include
	
This command will build `libuconv.a` in the directory where
`buildunits` was called.

If you need a different name for your library, then you could rename
it or use the flag `-l library-name`. Referring the previous example,
you could perform:

	buildunits -U my-units.H -H myproject/include -l my-units.a

#### Usage in your project

`uconv` internally uses several tables for storing physical quantities
names, units and conversions. For this reason, it is imperative to
explicitly initialize the library. The most recommended way for doing
that is with `UnitsInstancer` class, which is a singleton and that must
be called before any use of `uconv`. As general rule, we recommend to
instantiate just next the `uconv-list.H` header inclusion. Some such
this:

	# include <uconv-list.H>
	UnitsInstancer init; // or any other name that you want
	// here you could put other header inclusions
	
Be careful with a double instantiation that could cause a linking
conflict. You could avoid that by using a macro guard:

    # ifndef UNITS_INSTANTIATED
    # define UNITS_INSTANTIATED 1
    UnitsInstancer init;
    # endif

### Building Requirements

You will need `Aleph-w` library, which can be downloaded from
<https://github.com/lrleon/Aleph-w> and the Niels Lohmann (nlohmann) json
library, which can be downloaded from <https://github.com/nlohmann/json>.

In order to build the library, you will need to have installed `Ruby`,
given that the scripts are written in this language.

`uconv` has only been tested on Linux systems, but it is supposed to
run without problems on other systems where `Aleph-w` library is
installed. 

### Running Tests

Unit test cases are located it `Tests` directory. For performing
them, you will need `googletest`
<https://github.com/google/googletest>.

For executing all the tests:

    ./all-test
	
For executing a specific test:

	./run-test -f test-file
	
Demo tests are located in `tests` directory. Inside `tests` directory
execute

	make all

You will have the following executables:

1. `convert`: simple unit converter.

2. `vector-convert`: vector unit converter.

3. `test-all-units`: a unit bounds tester given a physical quantity.

## License

Since `uconv` depends on components that are licensed GNU GPL v3,
`uconv` is also licensed on the GNU GPL v3.

See
[LICENSE](https://github.com/lrleon/uconv/blob/master/LICENSE). COPYRIGHT
(c) 2018, Ixhel Mejias, Alberto Valderrama, Fernando Montilla, Eduardo
Valderrama, Neylith Quintero, Felix Buccellato, Virginia Buccellato
and Leandro Rabindranath Leon
