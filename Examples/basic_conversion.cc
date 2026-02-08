#include <iostream>
#include <uconv.H>
#include <units/length.H>
#include <units/temperature.H>

// Instantiate the units system (required once in the program)
UnitsInstancer init;


int main() {
    std::cout << "=== Example 1: Basic Conversion ===" << std::endl;

    // Definition of quantities with strong types
    Quantity<meter> length = 10.0;
    Quantity<foot> width = 50.0;

    std::cout << "Initial length: " << length << std::endl;
    std::cout << "Initial width: " << width << std::endl;

    // Arithmetic operations: automatic conversion
    // 'width' is converted to 'meter' before adding
    Quantity<meter> total = length + width;

    std::cout << "Total (length + width) in meters: " << total << std::endl;

    // Explicit conversion to another unit
    Quantity<yard> total_yards = total;
    std::cout << "Total in yards: " << total_yards << std::endl;

    // Example with temperature
    Quantity<Celsius> t_c = 100.0;
    Quantity<Fahrenheit> t_f = t_c;

    std::cout << "\nBoiling point temperature: " << t_c << " = " << t_f << std::endl;

    return 0;
}
