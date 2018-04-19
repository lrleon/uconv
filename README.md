# H1 Units definitions and their conversion library

# H2 Purpose
	
`uconv` is a C++ library that allows units definitions and conversions
between different physical units through simple classes for defining
and handling physical quantities, units measuring them and quantities
related to the units with transparent conversions. 

# H3 Physical Quantities

A physical quantity is defined with the macro 

    Declare_Physical_Unit(Physical_Quantity_Class_Name, 
	                      "Unit Symbol", "Unit LaTeX symbol",
						  "description");
						  
This macro declares a class defining a physical quantity. For example,
we can define class named `Temperature`, around which temperature units
would be grouped, as follows:

    Declare_Physical_Quantity(Temperature, "T", "T",
			  "Average thermal energy of the particles in a substance");
			  
# H3 Units Definition

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

# H3 Defining Unit Conversions

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

# H3 Defining and Using Quantities

There are two ways for defining a quantity with its unit, everyone
with its own class:

1. `Quantity<Unit_Class_Name>`: a quantity whose unit is known in
   compiling time.
   
2. `VtlQuantity`: a quantity whose unit is known in run time.

# H4 `Quantity` class

# H4 `VltQuantity` class

# H3 Defining bounds tolerance

# H2 Requirements

- Aleph-w library, which can be downloaded from
  <https://github.com/lrleon/Aleph-w>. 

- Niels Lohmann (nlohmann) json library, which can be downloaded from 
  <https://github.com/nlohmann/json>.

`uconv` has only been tested on Linux systems, but it is supposed to
run without problems on other systems where Aleph-w library is
installed. 

# H2 Integration

# H2 Licence

# H2 Examples
